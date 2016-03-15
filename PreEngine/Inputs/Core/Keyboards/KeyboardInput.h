#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "../../../Core/System.h"
#include "../../../Windows/GLWindow.h"
#include "../../../Core/Events/EventChannel.h"
#include "../../../Core/System.h"

#include "KeyboardEvents.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Keyboards
			{
				using namespace PreEngine::Core;
				using namespace PreEngine::Core::Events;
				using namespace PreEngine::Inputs::Core::Keyboards::Events;

				class KeyboardInput : public System
				{
				private:
					PreEngine::Windows::IWindow<GLFWwindow>* m_window;

				public:
					KeyboardInput(PreEngine::Windows::IWindow<GLFWwindow>* window);

					virtual ~KeyboardInput();

				public:
					bool Init();

					void Update(float deltaTime);

					void ShutDown();

				public:
					static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
				};
			}
		}
	}
}

#endif