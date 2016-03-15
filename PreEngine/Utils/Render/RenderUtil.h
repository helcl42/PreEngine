#ifndef RENDER_UTIL_H
#define RENDER_UTIL_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Render
		{
			class RenderUtil
			{
			public:
				static glm::mat4 GetPerspectiveProjectionMatrix(int w, int h, float fov, float nearClippingPlane, float farClippingPlane);

				static glm::mat4 GetOrthographicProjectionMatrix(int left, int top, int w, int h);

				static glm::mat4 GetViewMatrix(const glm::vec3& eyePosition, const glm::vec3& lookAtPosition, const glm::vec3& up);

				static glm::mat4 GetDepthBiasMatrix();

				static float GetAspectRatio(unsigned int w, unsigned int h);

				static std::vector<unsigned int> GenerateAdjacentIndices(const std::vector<unsigned int>& indices);
			};
		}
	}
}

#endif