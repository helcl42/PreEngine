#include "FlyingCamera.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Cameras
		{
			FlyingCamera::FlyingCamera()
				: FlyingCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, 0.1f)
			{
			}

			FlyingCamera::FlyingCamera(glm::vec3 eye, glm::vec3 view, glm::vec3 up, float speed, float sensitivity)
				: m_eye(eye), m_view(view), m_up(up), m_speed(speed), m_sesitivity(sensitivity)
			{
				m_keyPressHandler = new EventHandler<FlyingCamera, Keyboards::Events::OnKeyPress>(this);
				m_keyReleaseHandler = new EventHandler<FlyingCamera, Keyboards::Events::OnKeyRelease>(this);
				m_mouseMoveHandler = new EventHandler<FlyingCamera, Mouses::Events::OnMouseMove>(this);
			}

			FlyingCamera::~FlyingCamera()
			{
				SAFE_DELETE(m_mouseMoveHandler);
				SAFE_DELETE(m_keyReleaseHandler);
				SAFE_DELETE(m_keyPressHandler);
			}

			void FlyingCamera::SetMovingKeys(int forward, int back, int left, int right)
			{
				m_forward = forward;
				m_back = back;
				m_left = left;
				m_right = right;

				m_workingKeys.clear();
				m_workingKeys.insert(std::pair<int, bool>(forward, false));
				m_workingKeys.insert(std::pair<int, bool>(back, false));
				m_workingKeys.insert(std::pair<int, bool>(left, false));
				m_workingKeys.insert(std::pair<int, bool>(right, false));
			}

			void FlyingCamera::Update(float deltaTime)
			{
				glm::vec3 move = m_view - m_eye;
				move = glm::normalize(move);
				move *= m_speed;

				glm::vec3 strafe = glm::cross(m_view - m_eye, m_up);
				strafe = glm::normalize(strafe);
				strafe *= m_speed;

				glm::vec3 moveBy;
				if (m_workingKeys[m_forward]) moveBy += move * deltaTime;
				if (m_workingKeys[m_back]) moveBy -= move * deltaTime;
				if (m_workingKeys[m_left]) moveBy -= strafe * deltaTime;
				if (m_workingKeys[m_right]) moveBy += strafe * deltaTime;

				m_eye += moveBy;
				m_view += moveBy;
			}

			glm::mat4 FlyingCamera::LookAt()
			{
				return glm::lookAt(m_eye, m_view, m_up);
			}

			float FlyingCamera::GetAngleX() const
			{
				glm::vec3 direction1 = m_view - m_eye;
				direction1 = glm::normalize(direction1);
				glm::vec3 direction2 = direction1;
				direction2.y = 0.0f;
				direction2 = glm::normalize(direction2);
				float angle = std::acosf(glm::dot(direction2, direction1));
				if (direction1.y < 0) angle *= -1.0f;
				return angle;
			}

			float FlyingCamera::GetAngleY() const
			{
				glm::vec3 direction = m_view - m_eye;
				direction.y = 0.0f;
				direction = glm::normalize(direction);
				float angle = std::acosf(glm::dot(glm::vec3(0.0f, 0.0f, -1.0f), direction));
				if (direction.x < 0.0f) angle = 360.0f - angle;
				return angle;
			}

			void FlyingCamera::RotateYByAngle(float inputAngle)
			{
				m_view -= m_eye;
				m_view = glm::rotate(m_view, inputAngle, glm::vec3(0.0f, 1.0f, 0.0f));
				m_view += m_eye;
			}

			void FlyingCamera::RotateXByAngle(float inputAngle)
			{
				glm::vec3 axis = glm::cross(m_view - m_eye, m_up);
				axis = glm::normalize(axis);
				float angle = inputAngle + GetAngleX();
				if (angle > -89.0f && angle < 89.0f)
				{
					m_view -= m_eye;
					m_view = glm::rotate(m_view, inputAngle, axis);
					m_view += m_eye;
				}
			}

			glm::vec3 FlyingCamera::GetEye() const
			{
				return m_eye;
			}

			void FlyingCamera::SetEye(glm::vec3 eye)
			{
				m_eye = eye;
			}

			glm::vec3 FlyingCamera::GetView() const
			{
				return m_view;
			}

			void FlyingCamera::SetView(glm::vec3 view)
			{
				m_view = view;
			}

			glm::vec3 FlyingCamera::GetUp() const
			{
				return m_up;
			}

			void FlyingCamera::SetUp(glm::vec3 up)
			{
				m_up = up;
			}

			void FlyingCamera::operator() (const Keyboards::Events::OnKeyPress& press)
			{
				for (std::map<int, bool>::iterator it = m_workingKeys.begin(); it != m_workingKeys.end(); ++it)
				{
					if (press.key == it->first) it->second = true;
				}
			}

			void FlyingCamera::operator() (const Keyboards::Events::OnKeyRelease& release)
			{
				for (std::map<int, bool>::iterator it = m_workingKeys.begin(); it != m_workingKeys.end(); ++it)
				{
					if (release.key == it->first) it->second = false;
				}
			}

			void FlyingCamera::operator() (const Mouses::Events::OnMouseMove& move)
			{				
				if (move.diff.x != 0.0)
				{
					float deltaX = float(move.diff.x) * m_sesitivity;
					RotateYByAngle(deltaX);
				}

				if (move.diff.y != 0.0)
				{
					float screenDeltaY = float(move.diff.y) * m_sesitivity;
					RotateXByAngle(screenDeltaY);
				}
			}
		}
	}
}