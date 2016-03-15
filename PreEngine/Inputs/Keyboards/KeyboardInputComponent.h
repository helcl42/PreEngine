#ifndef KEYBOARD_INPUT_COMPONENT_H
#define KEYBOARD_INPUT_COMPONENT_H

#include "../../Core/Common.h"
#include "../../Core/Events/EventHandler.h"
#include "../Core/Keyboards/KeyboardEvents.h"
#include "IKeyboardListener.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Keyboards
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core::Keyboards::Events;

			class KeyboardInputComponent
			{
			private:
				std::set<IKeyboardListener*> m_keyboardListeners;

				std::set<int> m_workingKeys;

				EventHandler<KeyboardInputComponent, OnKeyPress>* m_keyPressHandler;

				EventHandler<KeyboardInputComponent, OnKeyRelease>* m_keyReleaseHandler;

			public:
				KeyboardInputComponent();

				virtual ~KeyboardInputComponent();

			public:
				void RegisterKeyboardListener(IKeyboardListener* listener);

				void UnregisterKeyboardListener(IKeyboardListener* listener);

				bool IsKeyPressed(int keyCode) const;

			public:
				void operator()(const OnKeyPress& press);

				void operator()(const OnKeyRelease& release);
			};
		}
	}
}

#endif