#include "Cube.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				Cube::Cube()
				{
				}

				Cube::~Cube()
				{
				}

				void Cube::Init()
				{
					Prepare();

					for (auto i = 0; i < 36; i++)
					{
						m_vbo->AddData(&cubeVertices[i], sizeof(glm::vec3));
						m_vbo->AddData(&cubeTexCoords[i % 6], sizeof(glm::vec2));
						m_vbo->AddData(&cubeNormals[i / 6], sizeof(glm::vec3));
					}

					Upload();

					m_isLoaded = true;
					m_countOfFaces = 12;
				}

				void Cube::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, 36);
				}

				void Cube::RenderBoundingBox()
				{
				}

				void Cube::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}