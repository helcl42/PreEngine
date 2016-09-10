#include "Circle.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				Circle::Circle(float radius, unsigned int numberOfSides)
					: m_radius(radius), m_numberOfSides(numberOfSides)
				{
				}

				Circle::~Circle()
				{
				}

				void Circle::Init()
				{
					Prepare();

					m_numberOfVertices = m_numberOfSides + 2;

					const float deltaAngle = TWO_PI_F / m_numberOfVertices;

					std::vector<glm::vec3> vertices(m_numberOfVertices);
					std::vector<glm::vec2> textureCoords(m_numberOfVertices);

					for (unsigned int i = 0; i < m_numberOfVertices; i++)
					{
						vertices[i] = glm::vec3(std::cos(deltaAngle * i) * m_radius, std::sin(deltaAngle * i) * m_radius, 0.0f);
						textureCoords[i] = glm::vec2((std::cos(deltaAngle * i) + 1.0) * 0.5, (std::sin(deltaAngle * i) + 1.0) * 0.5);
					}

					glm::vec3 normal(0.0f, 0.0f, 1.0f);
					for (unsigned int i = 0; i < m_numberOfVertices; i++)
					{
						m_vbo->AddData(&vertices[i], sizeof(glm::vec3));
						m_vbo->AddData(&textureCoords[i], sizeof(glm::vec2));
						m_vbo->AddData(&normal, sizeof(glm::vec3));
					}

					Upload();

					m_isLoaded = true;
				}

				void Circle::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, m_numberOfVertices);
				}

				void Circle::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}