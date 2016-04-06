#include "Torus.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				Torus::Torus(float radius, float tubeRadius, unsigned int subDivAround, unsigned int subDivTube)
					: m_radius(radius), m_tubeRadius(tubeRadius), m_subDivAround(subDivAround), m_subDivTube(subDivTube)
				{
				}

				Torus::~Torus()
				{
				}

				void Torus::Init()
				{
					Prepare();

					float addAngleAround = 360.0f / (float)m_subDivAround;
					float addAngleTube = 360.0f / (float)m_subDivTube;

					float currentAngleAround = 0.0f;
					unsigned int stepsAround = 1;
					unsigned int facesAdded = 0;

					while (stepsAround <= m_subDivAround)
					{
						float sineAround = std::sinf(glm::radians(currentAngleAround));
						float cosineAround = std::cosf(glm::radians(currentAngleAround));
						glm::vec3 direction1(sineAround, cosineAround, 0.0f);

						float nextAngleAround = currentAngleAround + addAngleAround;
						float nextSineAround = std::sinf(glm::radians(nextAngleAround));
						float nextCosineAround = std::cosf(glm::radians(nextAngleAround));
						glm::vec3 direction2(nextSineAround, nextCosineAround, 0.0f);

						float currentAngleTube = 0.0f;

						unsigned int iStepsTube = 1;
						while (iStepsTube <= m_subDivTube)
						{
							float sineTube = std::sinf(glm::radians(currentAngleTube));
							float cosineTube = std::cosf(glm::radians(currentAngleTube));
							float nextAngleTube = currentAngleTube + addAngleTube;
							float nextSineTube = std::sinf(glm::radians(nextAngleTube));
							float nextCosineTube = std::cosf(glm::radians(nextAngleTube));

							glm::vec3 middle1 = direction1 * (m_radius - m_tubeRadius / 2);
							glm::vec3 middle2 = direction2 * (m_radius - m_tubeRadius / 2);

							glm::vec3 quadPoints[] =
							{
								middle1 + glm::vec3(0.0f, 0.0f, -nextSineTube * m_tubeRadius) + direction1 * nextCosineTube * m_tubeRadius,
								middle1 + glm::vec3(0.0f, 0.0f, -sineTube * m_tubeRadius) + direction1 * cosineTube * m_tubeRadius,
								middle2 + glm::vec3(0.0f, 0.0f, -sineTube * m_tubeRadius) + direction2 * cosineTube * m_tubeRadius,
								middle2 + glm::vec3(0.0f, 0.0f, -nextSineTube * m_tubeRadius) + direction2 * nextCosineTube * m_tubeRadius
							};

							glm::vec3 normals[] =
							{
								glm::vec3(0.0f, 0.0f, -nextSineTube) + direction1 * nextCosineTube,
								glm::vec3(0.0f, 0.0f, -sineTube) + direction1 * cosineTube,
								glm::vec3(0.0f, 0.0f, -sineTube) + direction2 * cosineTube,
								glm::vec3(0.0f, 0.0f, -nextSineTube) + direction2 * nextCosineTube
							};

							glm::vec2 textureCoords[] =
							{
								glm::vec2(currentAngleAround / 360.0f, nextAngleTube / 360.0f),
								glm::vec2(currentAngleAround / 360.0f, currentAngleTube / 360.0f),
								glm::vec2(nextAngleAround / 360.0f, currentAngleTube / 360.0f),
								glm::vec2(nextAngleAround / 360.0f, nextAngleTube / 360.0f)
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
							currentAngleTube += addAngleTube;
							iStepsTube++;
						}
						currentAngleAround += addAngleAround;
						stepsAround++;
					}

					Upload();

					m_countOfFaces = facesAdded;
					m_isLoaded = true;
				}

				void Torus::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, m_countOfFaces * 3);
				}

				void Torus::RenderBoundingBox()
				{
				}

				void Torus::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}