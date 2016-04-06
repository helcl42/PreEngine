#include "Line.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				Line::Line(glm::vec3 vA, glm::vec3 vB)
					: m_vertexA(vA), m_vertexB(vB)
				{
				}

				Line::~Line()
				{
				}

				void Line::Init()
				{
					Prepare();

					glm::vec2 textureCoord(0.0);
					glm::vec3 normal(0.0);

					m_vbo->AddData(&m_vertexA, sizeof(glm::vec3));
					m_vbo->AddData(&textureCoord, sizeof(glm::vec2));					
					m_vbo->AddData(&normal, sizeof(glm::vec3));

					m_vbo->AddData(&m_vertexB, sizeof(glm::vec3));
					m_vbo->AddData(&textureCoord, sizeof(glm::vec2));
					m_vbo->AddData(&normal, sizeof(glm::vec3));

					Upload();

					m_isLoaded = true;
					m_countOfFaces = 1;
				}

				void Line::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, 2);
				}

				void Line::RenderBoundingBox()
				{
				}

				void Line::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}