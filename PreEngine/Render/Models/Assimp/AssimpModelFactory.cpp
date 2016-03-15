#include "AssimpModelFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Assimp
			{
				void AssimpModelFactory::ReadSingleFace(const aiMesh* mesh, const aiFace& face, AssimpModel* assimpModel)
				{
					for (unsigned int k = 0; k < 3; k++)
					{
						aiVector3D pos = mesh->mVertices[face.mIndices[k]];
						aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
						aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
						assimpModel->m_vbo->AddData(&pos, sizeof(aiVector3D));
						assimpModel->m_vbo->AddData(&uv, sizeof(aiVector2D));
						assimpModel->m_vbo->AddData(&normal, sizeof(aiVector3D));
					}
				}

				void AssimpModelFactory::AddBumpMapData(const aiMesh* mesh, const aiFace& face, AssimpModel* assimpModel)
				{
					aiVector3D temp0 = mesh->mVertices[face.mIndices[0]];
					glm::vec3 v0 = glm::vec3(temp0.x, temp0.y, temp0.z);
					aiVector3D temp1 = mesh->mVertices[face.mIndices[1]];
					glm::vec3 v1 = glm::vec3(temp1.x, temp1.y, temp1.z);
					aiVector3D temp2 = mesh->mVertices[face.mIndices[2]];
					glm::vec3 v2 = glm::vec3(temp2.x, temp2.y, temp2.z);

					temp0 = mesh->mTextureCoords[0][face.mIndices[0]];
					glm::vec3 uv0 = glm::vec3(temp0.x, temp0.y, temp0.z);
					temp1 = mesh->mTextureCoords[0][face.mIndices[1]];
					glm::vec3 uv1 = glm::vec3(temp1.x, temp1.y, temp1.z);
					temp2 = mesh->mTextureCoords[0][face.mIndices[2]];
					glm::vec3 uv2 = glm::vec3(temp2.x, temp2.y, temp2.z);

					glm::vec3 positionDiff1 = v1 - v0;
					glm::vec3 positionDiff2 = v2 - v0;

					glm::vec3 textureCoordDiff1 = uv1 - uv0;
					glm::vec3 textureCoordDiff2 = uv2 - uv0;

					float r = 1.0f / (textureCoordDiff1.x * textureCoordDiff2.y - textureCoordDiff2.x * textureCoordDiff1.y);
					glm::vec3 tangent = glm::normalize((positionDiff1 * textureCoordDiff2.y - positionDiff2 * textureCoordDiff1.y) * r);
					glm::vec3 biTangent = glm::normalize((positionDiff2 * textureCoordDiff1.x - positionDiff1 * textureCoordDiff1.x) * r);

					for (unsigned int k = 0; k < 3; k++)
					{
						assimpModel->m_vboBumpMap->AddData(&tangent, sizeof(glm::vec3));
						assimpModel->m_vboBumpMap->AddData(&biTangent, sizeof(glm::vec3));
					}
				}

				//void AssimpModelFactory::PrepareAdjacentIndices(const aiScene* scene, AssimpModel* assimpModel)
				//{
				//	unsigned int totalCountOfFaces = 0;
				//	std::vector<unsigned int> indices;
				//	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
				//	{
				//		const aiMesh* mesh = scene->mMeshes[i];
				//		totalCountOfFaces += mesh->mNumFaces;
				//		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
				//		{
				//			const aiFace& face = mesh->mFaces[j];
				//			for (unsigned int k = 0; k < 3; k++)
				//			{
				//				indices.push_back(face.mIndices[k]);
				//			}
				//		}
				//	}

				//	std::vector<unsigned int> adjacentIndices = RenderUtil::GenerateAdjacentIndices(indices);
				//	for (unsigned int i = 0; i < adjacentIndices.size(); ++i)
				//	{
				//		assimpModel->m_vboIndices->AddData(&adjacentIndices[i], sizeof(unsigned int));
				//	}
				//}

				int AssimpModelFactory::ReadSingleMesh(const aiMesh* mesh, AssimpModel* assimpModel, bool useBumpMap)
				{
					const int singleVertexTotalSize = 2 * sizeof(aiVector3D) + sizeof(aiVector2D);

					assimpModel->m_materialIndices.push_back(mesh->mMaterialIndex);

					int sizeBefore = assimpModel->m_vbo->GetCurrentSize();
					assimpModel->m_meshStartIndices.push_back(sizeBefore / singleVertexTotalSize);

					for (unsigned int j = 0; j < mesh->mNumFaces; j++)
					{
						const aiFace& face = mesh->mFaces[j];
						ReadSingleFace(mesh, face, assimpModel);
						if (useBumpMap) AddBumpMapData(mesh, face, assimpModel);
					}

					return sizeBefore;
				}

				void AssimpModelFactory::ReadMeshes(const aiScene* scene, AssimpModel* assimpModel, bool useBumpMap)
				{
					const int singleVertexTotalSize = 2 * sizeof(aiVector3D) + sizeof(aiVector2D);

					for (unsigned int i = 0; i < scene->mNumMeshes; i++)
					{
						const aiMesh* mesh = scene->mMeshes[i];
						int sizeBefore = ReadSingleMesh(mesh, assimpModel, useBumpMap);
						assimpModel->m_countOfFaces += mesh->mNumFaces;
						assimpModel->m_meshSizes.push_back((assimpModel->m_vbo->GetCurrentSize() - sizeBefore) / singleVertexTotalSize);
					}
				}

				int AssimpModelFactory::GetTextureIndex(AssimpModel* assimpModel, const std::string& fullPath)
				{
					int foundTextureIndex = -1;
					for (unsigned int j = 0; j < assimpModel->m_textures.size(); j++)
					{
						if (fullPath == assimpModel->m_textures[j]->GetPath())
						{
							foundTextureIndex = j;
							break;
						}
					}

					return foundTextureIndex;
				}

				void AssimpModelFactory::ReadMaterials(const aiScene* scene, AssimpModel* assimpModel, std::string filePath, std::string texturePath)
				{
					std::vector<int> materialRemap(scene->mNumMaterials);
					std::string directory = File::GetDirectoryPath(filePath);

					for (unsigned int i = 0; i < scene->mNumMaterials; i++)
					{
						const aiMaterial* material = scene->mMaterials[i];
						int textureIndex = 0;
						std::string fullPath;

						if (texturePath.empty())
						{
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

							std::string textureName = path.data;
							fullPath = directory + textureName;
						}
						else
						{
							fullPath = texturePath;
						}

						int foundTextureIndex = GetTextureIndex(assimpModel, fullPath);
						if (foundTextureIndex != -1)
						{
							materialRemap[i] = foundTextureIndex;
						}
						else
						{
							ITexture* newTexture = m_textureFactory->CreateTexture(fullPath, true);
							if (newTexture != NULL)
							{
								materialRemap[i] = (int)assimpModel->m_textures.size();
								assimpModel->m_textures.push_back(newTexture);
							}
						}
					}

					for (unsigned int i = 0; i < scene->mNumMeshes; i++)
					{
						int iOldIndex = assimpModel->m_materialIndices[i];
						assimpModel->m_materialIndices[i] = materialRemap[iOldIndex];
					}

					assimpModel->m_countOfMaterials = scene->mNumMaterials;
				}

				void AssimpModelFactory::BindData(AssimpModel* assimpModel, bool hasBumpMap)
				{
					glGenVertexArrays(1, &(assimpModel->m_vertexAttributeObject));
					glBindVertexArray(assimpModel->m_vertexAttributeObject);
					assimpModel->m_vbo->Create();
					assimpModel->m_vbo->Bind();
					assimpModel->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

					// vertex positions
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), 0);
					// texture coordinates
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)sizeof(aiVector3D));
					// normal vectors
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(aiVector3D) + sizeof(aiVector2D), (void*)(sizeof(aiVector3D) + sizeof(aiVector2D)));

					// indices
					//if (assimpModel->m_renderWithAdjacents)
					//{
					//	assimpModel->m_vboIndices->Create();
					//	assimpModel->m_vboIndices->Bind(GL_ELEMENT_ARRAY_BUFFER);
					//	assimpModel->m_vboIndices->UploadDataToGPU(GL_STATIC_DRAW);
					//}

					if (hasBumpMap)
					{
						assimpModel->m_vboBumpMap->Create();
						assimpModel->m_vboBumpMap->Bind();
						assimpModel->m_vboBumpMap->UploadDataToGPU(GL_STATIC_DRAW);

						// tangent vector
						glEnableVertexAttribArray(3);
						glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
						// biTangent vector
						glEnableVertexAttribArray(4);
						glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(aiVector3D)));
					}

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside
				}

				bool AssimpModelFactory::SetNormalTexture(AssimpModel* assimpModel, std::string normalTexturePath)
				{
					ITexture* newNormalTexture = m_textureFactory->CreateTexture(normalTexturePath);
					if (newNormalTexture != NULL)
					{
						assimpModel->m_normalTexrure = newNormalTexture;
						assimpModel->m_normalTexrure->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_NEAREST);
						return true;
					}
					return false;
				}

				AssimpModelFactory::AssimpModelFactory()
				{
				}

				AssimpModelFactory::~AssimpModelFactory()
				{
				}

				AssimpModel* AssimpModelFactory::CreateModelBase(std::string filePath, std::string texturePath, bool hasBumpMap)
				{
					AssimpModel* assimpModel = new AssimpModel();
					assimpModel->m_isLoaded = false;

					::Assimp::Importer importer;
					const aiScene* scene = importer.ReadFile(filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenSmoothNormals);
					if (!scene) throw new ModelException("Could not load model: " + filePath);

					ReadMeshes(scene, assimpModel, hasBumpMap);
					ReadMaterials(scene, assimpModel, filePath, texturePath);
					BindData(assimpModel, hasBumpMap);
					/*if (renderWithAdjacents)
					{
					assimpModel->m_renderWithAdjacents = true;
					PrepareAdjacentIndices(scene, assimpModel);
					assimpModel->m_renderWithAdjacents = true;
					}*/
					return assimpModel;
				}

				IModel* AssimpModelFactory::CreateModel(std::string filePath)
				{
					return CreateModel(filePath, "");
				}

				IModel* AssimpModelFactory::CreateModel(std::string filePath, std::string texturePath)
				{
					AssimpModel* assimpModel = CreateModelBase(filePath, texturePath);
					assimpModel->m_hasBumpMap = false;
					assimpModel->m_isLoaded = true;
					return assimpModel;
				}

				IModel* AssimpModelFactory::CreateModel(std::string filePath, std::string texturePath, std::string normalTexturePath)
				{
					AssimpModel* assimpModel = CreateModelBase(filePath, texturePath, true);					
					if (!SetNormalTexture(assimpModel, normalTexturePath)) throw new ModelException("Could not load Normal Map from: " + normalTexturePath);
					assimpModel->m_hasBumpMap = true;
					assimpModel->m_isLoaded = true;
					return assimpModel;
				}
			}
		}
	}
}
