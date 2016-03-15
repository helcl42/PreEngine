#include "MD2ModelFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				MD2ModelFactory::MD2ModelFactory()
				{					
				}

				MD2ModelFactory::~MD2ModelFactory()
				{
				}

				void MD2ModelFactory::PrepareModelStructures(MD2Model* model)
				{
					model->m_vboFrameVertices.resize(m_header.num_frames);
					for (int i = 0; i < m_header.num_frames; i++)
					{
						model->m_vboFrameVertices[i] = new VertexBufferObject();
						model->m_vboFrameVertices[i]->Create();
					}

					model->m_vboTextureCoords = new VertexBufferObject();
					model->m_vboTextureCoords->Create();
				}

				void MD2ModelFactory::ReadCommands(FILE* file)
				{
					m_commands.resize(m_header.num_glcmds);
					std::fseek(file, m_header.ofs_glcmds, SEEK_SET);
					std::fread(&m_commands[0], sizeof(int), m_header.num_glcmds, file);
				}

				void MD2ModelFactory::ReadFramesData(FILE* file)
				{
					char* buffer = new char[m_header.num_frames * m_header.framesize];
					std::fseek(file, m_header.ofs_frames, SEEK_SET);
					std::fread(buffer, sizeof(char), m_header.num_frames * m_header.framesize, file);

					m_vertices.resize(m_header.num_frames, std::vector<glm::vec3>(m_header.num_xyz));
					m_normals.resize(m_header.num_frames, std::vector<int>(m_header.num_xyz));

					for (int i = 0; i < m_header.num_frames; i++)
					{
						AnimationFrame* framePtr = (AnimationFrame*)&buffer[m_header.framesize * i];

						for (int j = 0; j < m_header.num_xyz; j++)
						{
							m_vertices[i][j].x = framePtr->translate[0] + float(framePtr->verts[j].v[0]) * framePtr->scale[0];
							m_vertices[i][j].y = framePtr->translate[1] + float(framePtr->verts[j].v[1]) * framePtr->scale[1];
							m_vertices[i][j].z = framePtr->translate[2] + float(framePtr->verts[j].v[2]) * framePtr->scale[2];

							m_normals[i][j] = framePtr->verts[j].lightnormalindex;
						}
					}

					SAFE_DELETE_ARRAY(buffer);
				}

				void MD2ModelFactory::ReadCommandData(MD2Model* model)
				{
					for (unsigned int i = 0;;)
					{
						int action = m_commands[i];
						if (action == 0) break;

						int renderMode = action < 0 ? GL_TRIANGLE_FAN : GL_TRIANGLE_STRIP;
						int numberOfVertices = action < 0 ? -action : action;
						i++;

						model->m_renderModes.push_back(renderMode);
						model->m_numberOfRenderedVertices.push_back(numberOfVertices);

						for (int j = 0; j < numberOfVertices; j++)
						{
							float s = *((float*)(&m_commands[i++]));
							float t = *((float*)(&m_commands[i++]));
							t = 1.0f - t;

							model->m_vboTextureCoords->AddData(&s, sizeof(float));
							model->m_vboTextureCoords->AddData(&t, sizeof(float));

							int vi = m_commands[i++];
							for (int k = 0; k < m_header.num_frames; k++)
							{
								model->m_vboFrameVertices[k]->AddData(&m_vertices[k][vi], 3 * sizeof(float));
								model->m_vboFrameVertices[k]->AddData(&m_normals[k][vi], 3 * sizeof(float));
							}
						}
					}
				}

				void MD2ModelFactory::BindData(MD2Model* model)
				{
					glGenVertexArrays(1, &(model->m_vertexArrayObject));
					glBindVertexArray(model->m_vertexArrayObject);

					for (int i = 0; i < m_header.num_frames; i++)
					{
						model->m_vboFrameVertices[i]->Bind();
						model->m_vboFrameVertices[i]->UploadDataToGPU(GL_STATIC_DRAW);
					}

					model->m_vboFrameVertices[0]->Bind();

					// vertex positions
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
					// vertex positions next frame
					glEnableVertexAttribArray(3);
					glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

					// normals
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (GLvoid*)sizeof(glm::vec3));
					// normals next frame
					glEnableVertexAttribArray(4);
					glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (GLvoid*)sizeof(glm::vec3));

					model->m_vboTextureCoords->Bind();
					model->m_vboTextureCoords->UploadDataToGPU(GL_STATIC_DRAW);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside
				}

				void MD2ModelFactory::SetTexture(MD2Model* model, std::string filePath)
				{
					std::string extensitons[] = { "jpg", "jpeg", "png", "bmp", "tga" };
					std::string basePath = filePath.substr(0, filePath.find_last_of('.') + 1);
					for (unsigned int i = 0; i < 5; i++)
					{
						ITexture* newTexture = m_textureFactory->CreateTexture(basePath + extensitons[i], true);
						if (newTexture != NULL)
						{
							newTexture->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
							model->m_texture = newTexture;
							break;
						}
					}
				}

				MD2Model* MD2ModelFactory::CreateModel(const std::string& filePath)
				{
					FILE* file;
					fopen_s(&file, filePath.c_str(), "rb");
					std::fread(&m_header, sizeof(AnimationHeader), 1, file);

					ReadFramesData(file);
					ReadCommands(file);

					MD2Model* model = new MD2Model();

					PrepareModelStructures(model);

					ReadCommandData(model);
					BindData(model);
					SetTexture(model, filePath);

					std::fclose(file);
					return model;
				}
			}
		}
	}
}