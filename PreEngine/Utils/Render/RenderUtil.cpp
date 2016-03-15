#include "RenderUtil.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Render
		{
			glm::mat4 RenderUtil::GetPerspectiveProjectionMatrix(int w, int h, float fov, float nearClippingPlane, float farClippingPlane)
			{
				return glm::perspective(glm::radians(fov), GetAspectRatio(w, h), nearClippingPlane, farClippingPlane);
			}

			glm::mat4 RenderUtil::GetOrthographicProjectionMatrix(int left, int top, int w, int h)
			{
				return glm::ortho((float)left, (float)w, (float)top, (float)h);
			}

			glm::mat4 RenderUtil::GetViewMatrix(const glm::vec3& eyePosition, const glm::vec3& lookAtPosition, const glm::vec3& up)
			{
				return glm::lookAt(eyePosition, lookAtPosition, up);
			}

			glm::mat4 RenderUtil::GetDepthBiasMatrix()
			{
				return glm::mat4(
					0.5f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.5f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.5f, 0.0f,
					0.5f, 0.5f, 0.5f, 1.0f
				);
			}

			float RenderUtil::GetAspectRatio(unsigned int w, unsigned int h)
			{
				return (float)w / (float)h;
			}

			std::vector<unsigned int> RenderUtil::GenerateAdjacentIndices(const std::vector<unsigned int>& indices)
			{
				std::vector<unsigned int> adjacentIndices;

				for (unsigned int i = 0; i < indices.size(); i += 3)
				{
					adjacentIndices.push_back(indices[i]);
					adjacentIndices.push_back(UINT_MAX);
					adjacentIndices.push_back(indices[i + 1]);
					adjacentIndices.push_back(UINT_MAX);
					adjacentIndices.push_back(indices[i + 2]);
					adjacentIndices.push_back(UINT_MAX);
				}

				for (unsigned int i = 0; i < adjacentIndices.size(); i += 6)
				{
					int a1 = adjacentIndices[i];
					int b1 = adjacentIndices[i + 2];
					int c1 = adjacentIndices[i + 4];

					// TODO refactor IT !!!
					for (unsigned int j = i + 6; j < adjacentIndices.size(); j += 6) 
					{
						int a2 = adjacentIndices[j];
						int b2 = adjacentIndices[j + 2];
						int c2 = adjacentIndices[j + 4];

						if ((a1 == a2 && b1 == b2) || (a1 == b2 && b1 == a2)) // Edge 1 == Edge 1
						{
							adjacentIndices[i + 1] = c2;
							adjacentIndices[j + 1] = c1;
						}

						if ((a1 == b2 && b1 == c2) || (a1 == c2 && b1 == b2)) // Edge 1 == Edge 2
						{
							adjacentIndices[i + 1] = a2;
							adjacentIndices[j + 3] = c1;
						}

						if ((a1 == c2 && b1 == a2) || (a1 == a2 && b1 == c2)) // Edge 1 == Edge 3
						{
							adjacentIndices[i + 1] = b2;
							adjacentIndices[j + 5] = c1;
						}

						if ((b1 == a2 && c1 == b2) || (b1 == b2 && c1 == a2)) // Edge 2 == Edge 1
						{
							adjacentIndices[i + 3] = c2;
							adjacentIndices[j + 1] = a1;
						}

						if ((b1 == b2 && c1 == c2) || (b1 == c2 && c1 == b2)) // Edge 2 == Edge 2
						{
							adjacentIndices[i + 3] = a2;
							adjacentIndices[j + 3] = a1;
						}

						if ((b1 == c2 && c1 == a2) || (b1 == a2 && c1 == c2)) // Edge 2 == Edge 3
						{
							adjacentIndices[i + 3] = b2;
							adjacentIndices[j + 5] = a1;
						}

						if ((c1 == a2 && a1 == b2) || (c1 == b2 && a1 == a2)) // Edge 3 == Edge 1
						{
							adjacentIndices[i + 5] = c2;
							adjacentIndices[j + 1] = b1;
						}

						if ((c1 == b2 && a1 == c2) || (c1 == c2 && a1 == b2)) // Edge 3 == Edge 2
						{
							adjacentIndices[i + 5] = a2;
							adjacentIndices[j + 3] = b1;
						}

						if ((c1 == c2 && a1 == a2) || (c1 == a2 && a1 == c2)) // Edge 3 == Edge 3
						{
							adjacentIndices[i + 5] = b2;
							adjacentIndices[j + 5] = b1;
						}
					}
				}

				// Look for any outside edges
				for (unsigned int i = 0; i < adjacentIndices.size(); i += 6)
				{
					if (adjacentIndices[i + 1] == UINT_MAX) adjacentIndices[i + 1] = adjacentIndices[i + 4];
					if (adjacentIndices[i + 3] == UINT_MAX) adjacentIndices[i + 3] = adjacentIndices[i];
					if (adjacentIndices[i + 5] == UINT_MAX) adjacentIndices[i + 5] = adjacentIndices[i + 2];
				}

				return adjacentIndices;
			}
		}
	}
}