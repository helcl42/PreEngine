#include "WalkingCamera.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			WalkingCamera::WalkingCamera()
				: WalkingCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f)
			{
			}

			WalkingCamera::WalkingCamera(glm::vec3 eye, glm::vec3 view, glm::vec3 up, float speed)
				: m_eye(eye), m_view(view), m_up(up), m_speed(speed)
			{
				m_keyPressHandler = new EventHandler<WalkingCamera, Keyboards::Events::OnKeyPress>(this);
				m_keyReleaseHandler = new EventHandler<WalkingCamera, Keyboards::Events::OnKeyRelease>(this);

				m_workingKeys.insert(std::pair<int, bool>(GLFW_KEY_A, false));
				m_workingKeys.insert(std::pair<int, bool>(GLFW_KEY_S, false));
				m_workingKeys.insert(std::pair<int, bool>(GLFW_KEY_F, false));
				m_workingKeys.insert(std::pair<int, bool>(GLFW_KEY_W, false));
			}

			WalkingCamera::~WalkingCamera()
			{
				SAFE_DELETE(m_keyReleaseHandler);
				SAFE_DELETE(m_keyPressHandler);
			}

			glm::mat4 WalkingCamera::LookAt()
			{
				return glm::lookAt(m_eye, m_view, m_up);
			}

			void WalkingCamera::Move(float by)
			{
				glm::vec3 direction = m_view - m_eye;
				direction *= by;
				m_eye += direction;
				m_view += direction;
			}

			void WalkingCamera::RotateViewY(float angle)
			{
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
				glm::vec3 direction = m_view - m_eye;
				glm::vec4 newView = rotation * glm::vec4(direction, 1.0f);
				m_view = glm::vec3(newView.x, newView.y, newView.z);
				m_view += m_eye;
			}

			void WalkingCamera::Update(float deltaTime)
			{
				if (m_workingKeys[GLFW_KEY_W]) Move(m_speed * deltaTime);
				if (m_workingKeys[GLFW_KEY_S]) Move(-m_speed * deltaTime);
				if (m_workingKeys[GLFW_KEY_A]) RotateViewY(90.0f * deltaTime);
				if (m_workingKeys[GLFW_KEY_D]) RotateViewY(-90.0f * deltaTime);
			}

			glm::vec3 WalkingCamera::GetEye() const
			{
				return m_eye;
			}

			glm::vec3 WalkingCamera::GetView() const
			{
				return m_view;
			}

			glm::vec3 WalkingCamera::GetUp() const
			{
				return m_up;
			}

			void WalkingCamera::operator() (const Keyboards::Events::OnKeyPress& press)
			{
				for (std::map<int, bool>::iterator it = m_workingKeys.begin(); it != m_workingKeys.end(); ++it)
				{
					if (press.key == it->first) it->second = true;
				}
			}

			void WalkingCamera::operator() (const Keyboards::Events::OnKeyRelease& release)
			{
				for (std::map<int, bool>::iterator it = m_workingKeys.begin(); it != m_workingKeys.end(); ++it)
				{
					if (release.key == it->first) it->second = false;
				}
			}
		}
	}
}