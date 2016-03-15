#include "Plane.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				Plane::Plane(float xsize, float zsize, unsigned int xdivs, unsigned int zdivs, float smax, float tmax)
					: m_xSize(xsize), m_zSize(zsize), m_xDivs(xdivs), m_zDivs(zdivs), m_sMax(smax), m_tMax(tmax)
				{
					m_vboIndices = new VertexBufferObject();
				}

				Plane::~Plane()
				{
					SAFE_DELETE(m_vboIndices);
				}

				void Plane::GerateData()
				{
					float x2 = m_xSize / 2.0f;
					float z2 = m_zSize / 2.0f;
					float iFactor = (float)m_zSize / m_zDivs;
					float jFactor = (float)m_xSize / m_xDivs;
					float texi = (float)m_sMax / m_zDivs;
					float texj = (float)m_tMax / m_xDivs;
					float x, z;
					for (unsigned int i = 0; i <= m_zDivs; i++)
					{
						z = iFactor * i - z2;
						for (unsigned int j = 0; j <= m_xDivs; j++)
						{
							x = jFactor * j - x2;
							glm::vec3 vertex(x, 0.0f, z);
							m_vbo->AddData(&vertex, sizeof(glm::vec3));

							glm::vec2 textureCoord(j * texi, i * texj);
							m_vbo->AddData(&textureCoord, sizeof(glm::vec2));

							glm::vec3 normal(0.0f, 1.0f, 0.0f);
							m_vbo->AddData(&normal, sizeof(glm::vec3));
						}
					}
				}

				void Plane::GenerateDataIndices()
				{
					unsigned int rowStart, nextRowStart;
					for (unsigned int i = 0; i < m_zDivs; i++)
					{
						rowStart = i * (m_xDivs + 1);
						nextRowStart = (i + 1) * (m_xDivs + 1);
						for (unsigned int j = 0; j < m_xDivs; j++)
						{
							unsigned int indices[] =
							{
								rowStart + j,
								nextRowStart + j,
								nextRowStart + j + 1,
								rowStart + j,
								nextRowStart + j + 1,
								rowStart + j + 1
							};

							m_vboIndices->AddData(indices, 6 * sizeof(unsigned int));
						}
					}
				}

				void Plane::Init()
				{
					m_countOfFaces = m_xDivs * m_zDivs;

					m_vbo->Create(m_countOfFaces);
					m_vbo->Bind();

					GerateData();

					m_vboIndices->Create();
					m_vboIndices->Bind();

					GenerateDataIndices();

					m_vbo->Bind();
					m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

					glGenVertexArrays(1, &m_vertexArrayObject);
					glBindVertexArray(m_vertexArrayObject);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

					m_vboIndices->Bind(GL_ELEMENT_ARRAY_BUFFER);
					m_vboIndices->UploadDataToGPU(GL_STATIC_DRAW);

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside
				}

				void Plane::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawElements(how, 6 * m_countOfFaces, GL_UNSIGNED_INT, NULL);
				}

				void Plane::RenderBoundingBox()
				{
				}

				void Plane::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}