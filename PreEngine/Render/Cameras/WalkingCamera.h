#ifndef WALKING_CAMERA_H
#define WALKING_CAMERA_H

#include "../../Core/Common.h"

#include "../../Core/Events/EventHandler.h"
#include "../../Inputs/Core/Keyboards/KeyboardEvents.h"

#include "IWalkingCamera.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core;

			class WalkingCamera : public IWalkingCamera
			{
			private:
				glm::vec3 m_eye;

				glm::vec3 m_view;

				glm::vec3 m_up;

				float m_speed;

				std::map<int, bool> m_workingKeys;

				EventHandler<WalkingCamera, Keyboards::Events::OnKeyPress>* m_keyPressHandler;

				EventHandler<WalkingCamera, Keyboards::Events::OnKeyRelease>* m_keyReleaseHandler;

			public:
				WalkingCamera();

				WalkingCamera(glm::vec3 eye, glm::vec3 view, glm::vec3 up, float speed);

				virtual ~WalkingCamera();

			public:
				glm::mat4 LookAt();

				void Update(float deltaTime);

				void Move(float by);

				void RotateViewY(float angle);

				glm::vec3 GetEye() const;

				glm::vec3 GetView() const;

				glm::vec3 GetUp() const;

				void operator() (const Keyboards::Events::OnKeyPress& press);

				void operator() (const Keyboards::Events::OnKeyRelease& release);
			};
		}
	}
}

#endif


