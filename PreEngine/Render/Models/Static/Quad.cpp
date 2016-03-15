#include "Quad.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				Quad::Quad(QuadType type)
					: m_type(type)
				{
				}

				Quad::~Quad()
				{
				}

				void Quad::Init()
				{
					Prepare();

					glm::vec3 planeVertices[4];

					if (m_type == QuadType::TOP)
					{
						planeVertices[0] = glm::vec3(-1.0f, 0.0f, 0.0f);
						planeVertices[1] = glm::vec3(1.0f, 0.0f, 0.0f);
						planeVertices[2] = glm::vec3(1.0f, 1.0f, 0.0f);
						planeVertices[3] = glm::vec3(-1.0f, 1.0f, 0.0f);
					} 
					else if (m_type == QuadType::BOTTOM)
					{
						planeVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
						planeVertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
						planeVertices[2] = glm::vec3(1.0f, 0.0f, 0.0f);
						planeVertices[3] = glm::vec3(-1.0f, 0.0f, 0.0f);
					}
					else if (m_type == QuadType::LEFT)
					{
						planeVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
						planeVertices[1] = glm::vec3(0.0f, -1.0f, 0.0f);
						planeVertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);
						planeVertices[3] = glm::vec3(-1.0f, 1.0f, 0.0f);
					}
					else if (m_type == QuadType::RIGHT)
					{
						planeVertices[0] = glm::vec3(0.0f, -1.0f, 0.0f);
						planeVertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
						planeVertices[2] = glm::vec3(1.0f, 1.0f, 0.0f);
						planeVertices[3] = glm::vec3(0.0f, 1.0f, 0.0f);
					}
					else // full is default
					{
						planeVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
						planeVertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
						planeVertices[2] = glm::vec3(1.0f, 1.0f, 0.0f);
						planeVertices[3] = glm::vec3(-1.0f, 1.0f, 0.0f);
					}

					glm::vec2 planeTexCoords[] =
					{
						glm::vec2(0.0f, 0.0f),
						glm::vec2(1.0f, 0.0f),
						glm::vec2(1.0f, 1.0f),
						glm::vec2(0.0f, 1.0f)
					};

					glm::vec3 normal(0.0f, 0.0f, 1.0f);
					for (unsigned int i = 0; i < 4; i++)
					{
						m_vbo->AddData(&planeVertices[i], sizeof(glm::vec3));
						m_vbo->AddData(&planeTexCoords[i], sizeof(glm::vec2));
						m_vbo->AddData(&normal, sizeof(glm::vec3));
					}

					Upload();

					m_isLoaded = true;
					m_countOfFaces = 1;
				}

				void Quad::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, 4);
				}

				void Quad::RenderBoundingBox()
				{
				}

				void Quad::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}