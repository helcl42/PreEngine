#ifndef IFLYING_CAMERA
#define IFLYING_CAMERA

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			class IFlyingCamera
			{
			public:
				virtual void SetMovingKeys(int forward, int back, int left, int right) = 0;

				virtual void Update(float deltaTime) = 0;

				virtual glm::mat4 LookAt() = 0;

				virtual float GetAngleX() const = 0;

				virtual float GetAngleY() const = 0;

				virtual void RotateYByAngle(float inputAngle) = 0;

				virtual void RotateXByAngle(float inputAngle) = 0;

				virtual glm::vec3 GetEye() const = 0;

				virtual void SetEye(glm::vec3 eye) = 0;

				virtual glm::vec3 GetView() const = 0;

				virtual void SetView(glm::vec3 view) = 0;

				virtual glm::vec3 GetUp() const = 0;

				virtual void SetUp(glm::vec3 up) = 0;

			public:
				virtual ~IFlyingCamera() {}
			};
		}
	}
}

#endif