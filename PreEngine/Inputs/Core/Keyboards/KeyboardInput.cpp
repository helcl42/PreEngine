#include "KeyboardInput.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Keyboards
			{
				KeyboardInput::KeyboardInput(PreEngine::Windows::IWindow<GLFWwindow>* window)
					: m_window(window)
				{
				}

				KeyboardInput::~KeyboardInput()
				{
				}

				bool KeyboardInput::Init()
				{
					glfwSetKeyCallback(m_window->GetWindow(), &KeyboardInput::KeyboardCallback);
					return true;
				}

				void KeyboardInput::Update(float deltaTime)
				{
				}

				void KeyboardInput::ShutDown()
				{
				}

				void KeyboardInput::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
				{
					switch (action)
					{
					case GLFW_PRESS:
						EventChannel::Broadcast(OnKeyPress{ key, modifiers });
						break;

					case GLFW_RELEASE:
						EventChannel::Broadcast(OnKeyRelease{ key, modifiers });
						break;
					}
				}
			}
		}
	}
}