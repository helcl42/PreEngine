#include "SkyBoxFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			SkyBoxFactory::SkyBoxFactory()
			{
				m_textureFactory = new TextureFactory();
			}

			SkyBoxFactory::~SkyBoxFactory()
			{
				SAFE_DELETE(m_textureFactory);
			}

			ISkyBox* SkyBoxFactory::CreateSkyBox(std::string dir, std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom)
			{
				SkyBox* skyBox = new SkyBox();

				skyBox->m_directory = dir;
				skyBox->m_front = front;
				skyBox->m_back = back;
				skyBox->m_left = left;
				skyBox->m_right = right;
				skyBox->m_top = top;
				skyBox->m_bottom = bottom;

				skyBox->m_textures[0] = m_textureFactory->CreateTexture(dir + front);
				skyBox->m_textures[1] = m_textureFactory->CreateTexture(dir + back);
				skyBox->m_textures[2] = m_textureFactory->CreateTexture(dir + left);
				skyBox->m_textures[3] = m_textureFactory->CreateTexture(dir + right);
				skyBox->m_textures[4] = m_textureFactory->CreateTexture(dir + top);
				skyBox->m_textures[5] = m_textureFactory->CreateTexture(dir + bottom);

				for (unsigned int i = 0; i < 6; i++)
				{
					skyBox->m_textures[i]->SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);
					skyBox->m_textures[i]->SetSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					skyBox->m_textures[i]->SetSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				}

				glGenVertexArrays(1, &(skyBox->m_vertexArrayObject));
				glBindVertexArray(skyBox->m_vertexArrayObject);

				skyBox->m_vbo->Create();
				skyBox->m_vbo->Bind();

				glm::vec3 skyBoxVertices[24] =
				{
					glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f), // Front face			
					glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f), // Back face			
					glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), // Left face			
					glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f), // Right face			
					glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(50.0f, 50.0f, 50.0f), // Top face			
					glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f), // Bottom face
				};

				glm::vec2 skyBoxTextureCoords[4] =
				{
					glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
				};

				glm::vec3 skyBoxNormals[6] =
				{
					glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)
				};

				for (unsigned int i = 0; i < 24; i++)
				{
					skyBox->m_vbo->AddData(&skyBoxVertices[i], sizeof(glm::vec3));
					skyBox->m_vbo->AddData(&skyBoxTextureCoords[i % 4], sizeof(glm::vec2));
					skyBox->m_vbo->AddData(&skyBoxNormals[i / 4], sizeof(glm::vec3));
				}

				skyBox->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

				// Vertex positions
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);

				// Texture coordinates
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));

				// Normal vectors
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

				return skyBox;
			}
		}
	}
}