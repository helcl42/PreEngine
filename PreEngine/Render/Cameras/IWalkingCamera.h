#ifndef IWALKING_CAMERA_H
#define IWALKING_CAMERA_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			class IWalkingCamera
			{
			public:
				virtual glm::mat4 LookAt() = 0;

				virtual void Update(float deltaTime) = 0;

				virtual void Move(float by) = 0;

				virtual void RotateViewY(float angle) = 0;

				virtual glm::vec3 GetEye() const = 0;

				virtual glm::vec3 GetView() const = 0;

				virtual glm::vec3 GetUp() const = 0;

			public:
				virtual ~IWalkingCamera() {}
			};
		}
	}
}

#endif