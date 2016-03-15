#include "Sphere.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				Sphere::Sphere(float radius, int subDivY, int subDivZ)
					: m_radius(radius), m_subDivY(subDivY), m_subDivZ(subDivZ)
				{
				}

				Sphere::~Sphere()
				{
				}

				void Sphere::Init()
				{
					Prepare();

					float addAngleY = 360.0f / float(m_subDivY), fAddAngleZ = 180.0f / float(m_subDivZ);
					float curAngleY = 0.0f;
					int stepsY = 1;
					int facesAdded = 0;

					while (stepsY <= m_subDivY)
					{
						float nextAngleY = curAngleY + addAngleY;
						float sineY = std::sinf(glm::radians(curAngleY)), fCosY = std::cosf(glm::radians(curAngleY));
						float nextSineY = std::sinf(glm::radians(nextAngleY)), fNextCosY = std::cosf(glm::radians(nextAngleY));
						glm::vec3 directionY(fCosY, 0.0f, -sineY), vNextDirY(fNextCosY, 0.0f, -nextSineY);
						float curAngleZ = 0.0f;
						int stepsZ = 1;
						while (stepsZ <= m_subDivZ)
						{
							float nextAngleZ = curAngleZ + fAddAngleZ;

							float sineZ = std::sinf(glm::radians(curAngleZ)), fCosZ = std::cosf(glm::radians(curAngleZ));
							float nextSineZ = std::sinf(glm::radians(nextAngleZ)), fNextCosZ = std::cosf(glm::radians(nextAngleZ));

							glm::vec3 quadPoints[] =
							{
								glm::vec3(directionY.x * sineZ * m_radius, fCosZ * m_radius, directionY.z * sineZ * m_radius),
								glm::vec3(directionY.x * nextSineZ * m_radius, fNextCosZ * m_radius, directionY.z * nextSineZ * m_radius),
								glm::vec3(vNextDirY.x * nextSineZ * m_radius, fNextCosZ * m_radius, vNextDirY.z * nextSineZ * m_radius),
								glm::vec3(vNextDirY.x * sineZ * m_radius, fCosZ * m_radius, vNextDirY.z * sineZ * m_radius),
							};

							glm::vec3 normals[] =
							{
								glm::normalize(quadPoints[0]),
								glm::normalize(quadPoints[1]),
								glm::normalize(quadPoints[2]),
								glm::normalize(quadPoints[3])
							};

							glm::vec2 textureCoords[4];

							float offset = 0.75f;
							float tx1 = 0.0f;
							float ty1 = 0.0f;
							for (unsigned int i = 0; i < 4; i++)
							{
								float tx = atan2f(normals[i].x, normals[i].z) / (2.0f * PI_F) + 0.5f;
								float ty = asinf(normals[i].y) / PI_F + 0.5f;
								if (i > 0)
								{
									if (tx < offset && tx1 > offset) tx += 1.0f;
									else if (tx > offset && tx1 < offset) tx -= 1.0f;
								}
								else
								{
									tx1 = tx;
									ty1 = ty;
								}
								textureCoords[i] = glm::vec2(tx, ty);
							}

							int iIndices[] = { 0, 1, 2, 2, 3, 0 };

							for (unsigned int i = 0; i < 6; i++)
							{
								int index = iIndices[i];
								m_vbo->AddData(&quadPoints[index], sizeof(glm::vec3));
								m_vbo->AddData(&textureCoords[index], sizeof(glm::vec2));
								m_vbo->AddData(&normals[index], sizeof(glm::vec3));
							}

							facesAdded += 2; // Keep count of added faces

							stepsZ++;
							curAngleZ += fAddAngleZ;
						}
						stepsY++;
						curAngleY += addAngleY;
					}

					Upload();

					m_countOfFaces = facesAdded;
					m_isLoaded = true;
				}

				void Sphere::Render(GLenum how)
				{
					glBindVertexArray(m_vertexArrayObject);
					glDrawArrays(how, 0, m_countOfFaces * 3);
				}

				void Sphere::RenderBoundingBox()
				{
				}

				void Sphere::Delete()
				{
					m_vbo->Delete();
					glDeleteVertexArrays(1, &m_vertexArrayObject);
				}
			}
		}
	}
}