#include "MouseInput.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Mouses
			{
				MouseInput::MouseInput(PreEngine::Windows::IWindow<GLFWwindow>* window)
					: m_window(window)
				{
				}

				MouseInput::~MouseInput()
				{
				}

				bool MouseInput::Init()
				{
					glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
					glfwSetMouseButtonCallback(m_window->GetWindow(), &MouseInput::MouseButtonCallback);
					glfwSetScrollCallback(m_window->GetWindow(), &MouseInput::MouseScrollCallback);
					return true;
				}

				void MouseInput::Update(float deltaTime)
				{
					glm::dvec2 newPosition;
					glfwGetCursorPos(m_window->GetWindow(), &newPosition.x, &newPosition.y);

					glm::dvec2 windowMeasures(m_window->GetWidth(), m_window->GetHeight());

					if (newPosition.x < m_actualMousePositionAbsolute.x - MIN_MOUSE_DELTA || newPosition.x > m_actualMousePositionAbsolute.x + MIN_MOUSE_DELTA
						|| newPosition.y < m_actualMousePositionAbsolute.y - MIN_MOUSE_DELTA || newPosition.y > m_actualMousePositionAbsolute.y + MIN_MOUSE_DELTA)
					{
						//if (m_window->IsFocused() || m_window->IsInFullScreen())
						//{
						m_channel.Broadcast(OnMouseMove{ newPosition, m_actualMousePosition, newPosition - m_actualMousePosition, windowMeasures });
						m_actualMousePositionAbsolute = newPosition;
						m_actualMousePosition = glm::dvec2(m_window->GetWidth() >> 1, m_window->GetHeight() >> 1);
						//}
					}

					if (m_mouseLockEnabled)
					{
						glfwSetCursorPos(m_window->GetWindow(), m_window->GetWidth() >> 1, m_window->GetHeight() >> 1);
					}
				}

				void MouseInput::ShutDown()
				{
				}

				void MouseInput::MouseScrollCallback(GLFWwindow* window, double xPos, double yPos)
				{
					glm::dvec2 newPosition(xPos, yPos);
					EventChannel::Broadcast(OnMouseScroll{ newPosition });
				}

				void MouseInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
				{
					glm::dvec2 newPosition;
					glfwGetCursorPos(window, &newPosition.x, &newPosition.y);

					switch (action)
					{
					case GLFW_PRESS:
						EventChannel::Broadcast(OnMouseButtonPress{ button, newPosition, modifiers });
						break;

					case GLFW_RELEASE:
						EventChannel::Broadcast(OnMouseButtonRelease{ button, newPosition, modifiers });
						break;
					}
				}

				void MouseInput::operator()(const OnMouseLockRequest& lockRequest)
				{
					m_mouseLockEnabled = lockRequest.lock;
				}

				void MouseInput::operator()(const OnMouseShowRequest& showRequest)
				{
					glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, showRequest.show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
				}
			}
		}
	}
}