#ifndef FLYING_CAMERA_H
#define FLYING_CAMERA_H

#include "../../Core/Common.h"

#include "../../Core/Events/EventHandler.h"
#include "../../Inputs/Core/Keyboards/KeyboardEvents.h"
#include "../../Inputs/Core/Mouses/MouseEvents.h"

#include "IFlyingCamera.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core;

			class FlyingCamera : public IFlyingCamera
			{
			private:
				int m_forward, m_back, m_left, m_right;

				glm::vec2 m_previousMousePosition;

				glm::vec2 m_currentMousePosition;

				glm::vec3 m_eye, m_view, m_up;

				float m_speed;

				float m_sesitivity;

				std::map<int, bool> m_workingKeys;

				EventHandler<FlyingCamera, Keyboards::Events::OnKeyPress>* m_keyPressHandler;

				EventHandler<FlyingCamera, Keyboards::Events::OnKeyRelease>* m_keyReleaseHandler;

				EventHandler<FlyingCamera, Mouses::Events::OnMouseMove>* m_mouseMoveHandler;

			public:
				FlyingCamera();

				FlyingCamera(glm::vec3 eye, glm::vec3 view, glm::vec3 up, float speed, float sensitivity);

				virtual ~FlyingCamera();

			public:
				void SetMovingKeys(int forward, int back, int left, int right);

				void Update(float deltaTime);

				glm::mat4 LookAt();

				float GetAngleX() const;

				float GetAngleY() const;

				void RotateYByAngle(float inputAngle);

				void RotateXByAngle(float inputAngle);

				glm::vec3 GetEye() const;

				void SetEye(glm::vec3 eye);

				glm::vec3 GetView() const;

				void SetView(glm::vec3 view);

				glm::vec3 GetUp() const;

				void SetUp(glm::vec3 up);

			public:
				void operator() (const Keyboards::Events::OnKeyPress& press);

				void operator() (const Keyboards::Events::OnKeyRelease& release);

				void operator() (const Mouses::Events::OnMouseMove& move);
			};
		}
	}
}

#endif // !FLYING_CAMERA_H


