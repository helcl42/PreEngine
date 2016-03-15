#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				AbstractDrawableObject::AbstractDrawableObject()
				{
					m_vbo = new VertexBufferObject();
				}

				AbstractDrawableObject::~AbstractDrawableObject()
				{
					SAFE_DELETE(m_vbo);
				}

				void AbstractDrawableObject::Prepare()
				{
					m_vbo->Create();

					glGenVertexArrays(1, &m_vertexArrayObject);
					glBindVertexArray(m_vertexArrayObject);

					m_vbo->Bind();
				}

				void AbstractDrawableObject::Upload()
				{
					m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside
				}

				void AbstractDrawableObject::SetDefaultTexturesEnabled(bool enabled)
				{
					m_defaultTexturesEnabled = enabled;
				}

				bool AbstractDrawableObject::IsDefaultTexturesEnabled() const
				{
					return m_defaultTexturesEnabled;
				}

				bool AbstractDrawableObject::IsLoaded() const
				{
					return m_isLoaded;
				}

				unsigned int AbstractDrawableObject::GetPolygonCount() const
				{
					return m_countOfFaces;
				}
			}
		}
	}
}
