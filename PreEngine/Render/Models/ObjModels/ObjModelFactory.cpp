#include "ObjModelFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace ObjModels
			{
				ObjModelFactory::ObjModelFactory()
				{
					Reset();
					m_fileReader = new FileReader();
				}

				ObjModelFactory::~ObjModelFactory()
				{
					SAFE_DELETE(m_fileReader);
				}

				void ObjModelFactory::Reset()
				{
					m_countOfFaces = 0;
					m_attrBitField = 0;
					m_vertices.clear();
					m_textureCoords.clear();
					m_normals.clear();
					m_lowerLeftFront = glm::vec3(999999.0f, 999999.0f, -999999.0f);
					m_upperRightBack = glm::vec3(-999999.0f, -999999.0f, 999999.0f);
				}

				ITexture* ObjModelFactory::LoadMaterial(std::string mtlFilePath)
				{
					ITexture* retMaterial = NULL;

					if (!m_fileReader->Open(mtlFilePath)) throw ModelException("Could not open material file: " + mtlFilePath);

					while (!m_fileReader->IsEOF())
					{
						std::string line = m_fileReader->ReadLine();
						size_t kaPosition = line.find("map_Ka");
						if (kaPosition != line.npos)
						{
							std::string filePath = m_fileReader->GetDirectoryPath() + line.substr(kaPosition + 6 + 1, line.size() - (kaPosition + 6 + 1));
							retMaterial = m_textureFactory->CreateTexture(filePath, true);
							retMaterial->SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_NEAREST_MIPMAP);
							break;
						}
					}

					m_fileReader->Close();
					return retMaterial;
				}

				void ObjModelFactory::ReadSingleVetexGroup(std::stringstream& ss)
				{
					glm::vec3 newVertex;
					int dimension = 0;
					while (dimension < 3 && ss >> newVertex[dimension])
					{
						dimension++;
					}

					m_vertices.push_back(newVertex);

					m_lowerLeftFront.x = std::min(m_lowerLeftFront.x, newVertex.x);
					m_lowerLeftFront.y = std::min(m_lowerLeftFront.y, newVertex.y);
					m_lowerLeftFront.z = std::max(m_lowerLeftFront.z, newVertex.z);

					m_upperRightBack.x = std::max(m_upperRightBack.x, newVertex.x);
					m_upperRightBack.y = std::max(m_upperRightBack.y, newVertex.y);
					m_upperRightBack.z = std::min(m_upperRightBack.z, newVertex.z);

					m_attrBitField |= 1;
				}

				void ObjModelFactory::ReadSingleTextureCoordinate(std::stringstream& ss)
				{
					glm::vec2 newCoord;
					int dimension = 0;

					while (dimension < 2 && ss >> newCoord[dimension])
					{
						dimension++;
					}

					m_textureCoords.push_back(newCoord);
					m_attrBitField |= 2;
				}

				void ObjModelFactory::ReadSingleNormal(std::stringstream& ss)
				{
					glm::vec3 newNormal;
					int dimension = 0;

					while (dimension < 3 && ss >> newNormal[dimension])
					{
						dimension++;
					}

					newNormal = glm::normalize(newNormal);
					m_normals.push_back(newNormal);
					m_attrBitField |= 4;
				}

				void ObjModelFactory::ReadSingleFace(ObjModel* objModel, std::stringstream& ss)
				{
					std::string sFaceData;

					while (ss >> sFaceData)
					{
						std::vector<std::string> data = StringUtils::Split(sFaceData, "/");
						unsigned int vertexIndex = 0, texCoordIndex = 0, normalIndex = 0;

						if (m_attrBitField & 1)
						{
							if (data.size() > 0 && data[0].size() > 0) vertexIndex = std::stoi(data[0]);
							else throw ModelException("Model has inconsistent vertices.");
						}

						if (m_attrBitField & 2)
						{
							if (data.size() >= 1 && data[1].size() > 0) texCoordIndex = std::stoi(data[1]);
							else throw ModelException("Model has inconsistent texture coordinates.");
						}

						if (m_attrBitField & 4)
						{
							if (data.size() >= 2 && data[2].size() > 0) normalIndex = std::stoi(data[2]);
							else throw ModelException("Model has inconsistent normals.");
						}

						if (vertexIndex > 0 && vertexIndex <= m_vertices.size()) objModel->m_vbo->AddData(&m_vertices[vertexIndex - 1], sizeof(glm::vec3));
						if (texCoordIndex > 0 && texCoordIndex <= m_textureCoords.size()) objModel->m_vbo->AddData(&m_textureCoords[texCoordIndex - 1], sizeof(glm::vec2));
						if (normalIndex > 0 && normalIndex <= m_normals.size()) objModel->m_vbo->AddData(&m_normals[normalIndex - 1], sizeof(glm::vec3));
					}
					m_countOfFaces++;
				}

				void ObjModelFactory::ReadSingleModelLine(ObjModel* objModel, std::string line)
				{
					std::stringstream ss(line);
					std::string type;

					ss >> type;
					if (type == "#") return;
					else if (type == "v") ReadSingleVetexGroup(ss);
					else if (type == "vt") ReadSingleTextureCoordinate(ss);
					else if (type == "vn") ReadSingleNormal(ss);
					else if (type == "f") ReadSingleFace(objModel, ss);
					else if (type == "s") return;
					else if (type == "usemtl") return;
				}

				void ObjModelFactory::BindData(ObjModel* objModel)
				{
					objModel->m_vbo->Create();
					objModel->m_vbo->Bind();
					objModel->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

					glGenVertexArrays(1, &(objModel->m_vertexAttributeObject));
					glBindVertexArray(objModel->m_vertexAttributeObject);

					int dataStride = 0;
					if (m_attrBitField & 1) dataStride += sizeof(glm::vec3);
					if (m_attrBitField & 2) dataStride += sizeof(glm::vec2);
					if (m_attrBitField & 4) dataStride += sizeof(glm::vec3);

					if (m_attrBitField & 1)
					{
						glEnableVertexAttribArray(0);
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, dataStride, 0);
					}

					if (m_attrBitField & 2)
					{
						glEnableVertexAttribArray(1);
						int dataOffset = 0;
						if (m_attrBitField & 1) dataOffset += sizeof(glm::vec3);
						glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, dataStride, (GLvoid*)dataOffset);
					}

					if (m_attrBitField & 4)
					{
						glEnableVertexAttribArray(2);
						int dataOffset = 0;
						if (m_attrBitField & 1) dataOffset += sizeof(glm::vec3);
						if (m_attrBitField & 2) dataOffset += sizeof(glm::vec2);
						glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, dataStride, (GLvoid*)dataOffset);
					}

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside
				}

				void ObjModelFactory::Center()
				{
					if (m_vertices.size() < 1) return;

					glm::vec3 maxPoint = m_vertices[0];
					glm::vec3 minPoint = m_vertices[0];

					// find the AABB
					for (unsigned int i = 0; i < m_vertices.size(); ++i)
					{
						glm::vec3& point = m_vertices[i];
						maxPoint.x = std::max(point.x, maxPoint.x);
						maxPoint.y = std::max(point.y, maxPoint.y);
						maxPoint.z = std::max(point.z, maxPoint.z);

						minPoint.x = std::min(point.x, minPoint.x);
						minPoint.y = std::min(point.y, minPoint.y);
						minPoint.z = std::min(point.z, minPoint.z);
					}

					// center of the AABB
					glm::vec3 center = glm::vec3((maxPoint.x + minPoint.x) / 2.0f, (maxPoint.y + minPoint.y) / 2.0f, (maxPoint.z + minPoint.z) / 2.0f);

					// translate center of the AABB to the origin
					for (unsigned int i = 0; i < m_vertices.size(); ++i)
					{
						glm::vec3& point = m_vertices[i];
						point = point - center;
					}
				}

				void ObjModelFactory::BindBoundingBoxData(ObjModel* objModel)
				{
					glGenVertexArrays(1, &(objModel->m_vertexAttributeObjectBB));
					glBindVertexArray(objModel->m_vertexAttributeObjectBB);

					glm::vec3 boundingBoxVerticies[] =
					{
						// front cube wall
						m_lowerLeftFront,
						glm::vec3(m_upperRightBack.x, m_lowerLeftFront.y, m_lowerLeftFront.z),
						glm::vec3(m_lowerLeftFront.x, m_upperRightBack.y, m_lowerLeftFront.z),
						glm::vec3(m_upperRightBack.x, m_upperRightBack.y, m_lowerLeftFront.z),

						// back cube wall
						glm::vec3(m_lowerLeftFront.x, m_lowerLeftFront.y, m_upperRightBack.z),
						glm::vec3(m_upperRightBack.x, m_lowerLeftFront.y, m_upperRightBack.z),
						glm::vec3(m_lowerLeftFront.x, m_upperRightBack.y, m_upperRightBack.z),
						m_upperRightBack
					};

					int indices[] = // index 8 == reset primitve index
					{
						0, 1, 2, 3, 8,
						4, 5, 6, 7, 8,
						4, 0, 6, 2, 8,
						1, 5, 3, 7, 8,
						2, 3, 6, 7, 8,
						0, 1, 4, 5
					};

					objModel->m_vboBB->Create();
					objModel->m_vboBB->Bind();

					objModel->m_vboBB->AddData(&boundingBoxVerticies, sizeof(boundingBoxVerticies));
					objModel->m_vboBB->UploadDataToGPU(GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

					objModel->m_vboBBIndices->Create();
					objModel->m_vboBBIndices->Bind(GL_ELEMENT_ARRAY_BUFFER);

					objModel->m_vboBBIndices->AddData(indices, sizeof(indices));
					objModel->m_vboBBIndices->UploadDataToGPU(GL_STATIC_DRAW);
				}

				IModel* ObjModelFactory::CreateModel(const std::string& filePath, const std::string& mtlFilPath)
				{
					ObjModel* objModel = new ObjModel();

					if (!m_fileReader->Open(filePath)) throw ModelException("Could not open .obj file: " + filePath);

					while (!m_fileReader->IsEOF())
					{
						std::string line = m_fileReader->ReadLine();
						if (line.size() <= 1) continue;
						ReadSingleModelLine(objModel, line);
					}

					m_fileReader->Close();

					if (m_attrBitField == 0) throw ModelException("Model consists of invalid data.");

					Center();
					BindData(objModel);
					BindBoundingBoxData(objModel);
					objModel->m_countOfFaces = m_countOfFaces;
					objModel->m_isLoaded = true;

					if (m_attrBitField & 2) objModel->m_ambientTexture = LoadMaterial(mtlFilPath);

					Reset();
					return objModel;
				}
			}
		}
	}
}