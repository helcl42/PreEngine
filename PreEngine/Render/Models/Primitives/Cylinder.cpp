#include "Cylinder.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				Cylinder::Cylinder(float radius, float height, unsigned int subDivAround, float mapU, float mapV)
					: m_radius(radius), m_height(height), m_subDivAround(subDivAround), m_mapU(mapU), m_mapV(mapV)
				{
				}

				Cylinder::~Cylinder()
				{
				}

				void Cylinder::Init()
				{
					Prepare();

					float addAngleAround = 360.0f / (float)(m_subDivAround - 1);
					float currentAngleAround = 0.0f;
					unsigned int stepsAround = 1;
					unsigned int facesAdded = 0;

					while (stepsAround <= m_subDivAround)
					{
						float sineAround = sinf(glm::radians(currentAngleAround));
						float cosineAround = cosf(glm::radians(currentAngleAround));
						glm::vec3 direction1(cosineAround, 0.0f, sineAround);

						float nextAngleAround = currentAngleAround + addAngleAround;
						float nextSineAround = sinf(glm::radians(nextAngleAround));
						float nextCosineAround = cosf(glm::radians(nextAngleAround));
						glm::vec3 direction2(nextCosineAround, 0.0f, nextSineAround);

						glm::vec3 quadPoints[] =
						{
							glm::vec3(0.0f, m_height, 0.0f) + direction1 * m_radius, direction1 * m_radius, direction2 * m_radius,
							glm::vec3(0.0f, m_height, 0.0f) + direction2 * m_radius
						};

						glm::vec2 textureCoords[] =
						{
							glm::vec2(m_mapU * currentAngleAround / 360.0f, m_mapV),
							glm::vec2(m_mapU * currentAngleAround / 360.0f, 0.0f),
							glm::vec2(m_mapU * nextAngleAround / 360.0f, 0.0f),
							glm::vec2(m_mapU * nextAngleAround / 360.0f, m_mapV)
						};

						glm::vec3 normals[] =
						{
							direction1,
							direction1,
							direction2,
							direction2
						};

						int indices[] = { 0, 1, 2, 2, 3, 0 };

						for (unsigned int i = 0; i < 6; i++)
						{
							int index = indices[i];
							m_vbo->AddData(&quadPoints[index], sizeof(glm::vec3));
							m_vbo->AddData(&textureCoords[index], sizeof(glm::vec2));
							m_vbo->AddData(&normals[index], sizeof(glm::vec3));
						}
						facesAdded += 2; // Keep count of added faces

						currentAngleAround += addAngleAround;
						stepsAround++;
					}

					Upload();

					m_countOfFaces = facesAdded;
					m_isLoaded = true;
				}

				void Cylinder::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, m_countOfFaces * 3);
				}

				void Cylinder::RenderBoundingBox()
				{
				}

				void Cylinder::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}