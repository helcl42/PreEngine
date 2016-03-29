#include "MD5ModelFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				MD5ModelFactory::MD5ModelFactory()
				{
				}

				MD5ModelFactory::~MD5ModelFactory()
				{
				}

				bool MD5ModelFactory::InitFromScene(const aiScene* pScene, MD5Model* model, const std::string& Filename)
				{
					std::vector<glm::vec3> Positions;
					std::vector<glm::vec3> Normals;
					std::vector<glm::vec2> TexCoords;
					std::vector<VertexBoneData> Bones;
					std::vector<unsigned int> Indices;

					unsigned int NumVertices = 0;
					unsigned int NumIndices = 0;

					model->m_meshEntries.resize(pScene->mNumMeshes);
					for (unsigned int i = 0; i < model->m_meshEntries.size(); i++)
					{
						model->m_meshEntries[i].materialIndex = pScene->mMeshes[i]->mMaterialIndex;
						model->m_meshEntries[i].numberOfIndices = pScene->mMeshes[i]->mNumFaces * 3;
						model->m_meshEntries[i].baseVertex = NumVertices;
						model->m_meshEntries[i].baseIndex = NumIndices;

						NumVertices += pScene->mMeshes[i]->mNumVertices;
						NumIndices += model->m_meshEntries[i].numberOfIndices;
					}

					Positions.reserve(NumVertices);
					Normals.reserve(NumVertices);
					TexCoords.reserve(NumVertices);
					Bones.resize(NumVertices);
					Indices.reserve(NumIndices);

					for (unsigned int i = 0; i < model->m_meshEntries.size(); i++)
					{
						const aiMesh* paiMesh = pScene->mMeshes[i];
						InitMesh(model, i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
					}

					BindData(model, Positions, Normals, TexCoords, Bones, Indices);
					return true;
				}

				void MD5ModelFactory::BindData(MD5Model* model, std::vector<glm::vec3>& Positions, std::vector<glm::vec3>& Normals, std::vector<glm::vec2>& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices)
				{
					glGenVertexArrays(1, &model->m_vertexAttributeObject);
					glBindVertexArray(model->m_vertexAttributeObject);

					GLuint buffers[NUM_VBs];
					glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(buffers), buffers);

					glBindBuffer(GL_ARRAY_BUFFER, buffers[POS_VB]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
					glEnableVertexAttribArray(POSITION_LOCATION);
					glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_VB]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
					glEnableVertexAttribArray(TEX_COORD_LOCATION);
					glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_VB]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
					glEnableVertexAttribArray(NORMAL_LOCATION);
					glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, buffers[BONE_VB]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
					glEnableVertexAttribArray(BONE_ID_LOCATION);
					glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
					glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
					glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(ARRAY_SIZE_IN_ELEMENTS(Bones[0].IDs) * sizeof(unsigned int)));

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

					glBindVertexArray(0);
				}

				void MD5ModelFactory::InitMesh(MD5Model* model, unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<glm::vec3>& Positions, std::vector<glm::vec3>& Normals, std::vector<glm::vec2>& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices)
				{
					const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
					for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
					{
						const aiVector3D* pPos = &(paiMesh->mVertices[i]);
						const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
						const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

						Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
						Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
						TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
					}

					LoadBones(model, MeshIndex, paiMesh, Bones);

					if (paiMesh->mFaces != NULL)
					{
						for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
						{
							const aiFace& Face = paiMesh->mFaces[i];
							assert(Face.mNumIndices == 3);
							Indices.push_back(Face.mIndices[0]);
							Indices.push_back(Face.mIndices[1]);
							Indices.push_back(Face.mIndices[2]);
						}
					}
				}

				void MD5ModelFactory::LoadBones(MD5Model* model, unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
				{
					for (unsigned int i = 0; i < pMesh->mNumBones; i++)
					{
						unsigned int BoneIndex = 0;
						std::string BoneName(pMesh->mBones[i]->mName.data);

						if (model->m_boneMapping.find(BoneName) == model->m_boneMapping.end())
						{
							BoneIndex = model->m_numBones;
							model->m_numBones++;
							BoneInfo bi;
							model->m_boneInfos.push_back(bi);
							model->m_boneInfos[BoneIndex].boneOffset = AIToGLMUtil::Mat4(pMesh->mBones[i]->mOffsetMatrix);
							model->m_boneMapping[BoneName] = BoneIndex;
						}
						else
						{
							BoneIndex = model->m_boneMapping[BoneName];
						}

						for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
						{
							unsigned int VertexID = model->m_meshEntries[MeshIndex].baseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
							float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
							Bones[VertexID].AddBoneData(BoneIndex, Weight);							
						}
					}
				}

				void MD5ModelFactory::InitMaterials(const aiScene* scene, MD5Model* model, std::string filePath)
				{
					model->m_countOfMaterials = 0;
					std::string directory = File::GetDirectoryPath(filePath);
					for (unsigned int i = 0; i < scene->mNumMaterials; i++)
					{
						const aiMaterial* material = scene->mMaterials[i];
						int textureIndex = 0;
						std::string fullPath;

						aiString path;
						bool ok = material->GetTexture(aiTextureType_SPECULAR, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_DIFFUSE, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_AMBIENT, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_EMISSIVE, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_NORMALS, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_HEIGHT, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_SHININESS, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_OPACITY, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_DISPLACEMENT, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_LIGHTMAP, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_REFLECTION, textureIndex, &path) == AI_SUCCESS;
						if (!ok) ok = material->GetTexture(aiTextureType_UNKNOWN, textureIndex, &path) == AI_SUCCESS;
						if (!ok) // FALLBACK
						{
							std::string folderPath = filePath;
							std::string baseFileName = folderPath.substr(folderPath.find_last_of("///") + 1);
							baseFileName = baseFileName.substr(0, baseFileName.find_last_of(".") + 1);
							folderPath = folderPath.substr(0, folderPath.find_last_of(".") + 1);
							std::string extensitons[] = { "jpg", "jpeg", "png", "bmp", "tga" };
							for (unsigned int i = 0; i < 5; i++)
							{
								if (File::Exists(folderPath + extensitons[i]))
								{
									baseFileName += extensitons[i];
									path = baseFileName.c_str();
									break;
								}
							}
						}

						std::string textureName(path.data);
						fullPath = directory + textureName;
						ITexture* newTexture = m_textureFactory->CreateTexture(fullPath, true);
						if (newTexture != NULL)
						{
							model->m_textures.push_back(newTexture);
							model->m_countOfMaterials++;
						}
					}
				}

				MD5Model* MD5ModelFactory::CreateModel(const std::string& filePath)
				{
					MD5Model* model = new MD5Model();
					const aiScene* pScene = model->importer.ReadFile(filePath.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenSmoothNormals);
					if (pScene)
					{
						model->m_scene = pScene;
						model->m_globalInverseTransform = glm::inverse(AIToGLMUtil::Mat4(pScene->mRootNode->mTransformation));
						InitFromScene(pScene, model, filePath);
						InitMaterials(pScene, model, filePath);
						model->m_isLoaded = true;						
					}
					else
					{
						throw ModelException("Could not load MD5 model: " + filePath + " Error: " + std::string(model->importer.GetErrorString()));
					}

					return model;
				}
			}
		}
	}
}