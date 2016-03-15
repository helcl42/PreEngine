#include "KeyboardInputComponent.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Keyboards
		{
			KeyboardInputComponent::KeyboardInputComponent()
			{
				m_keyPressHandler = new EventHandler<KeyboardInputComponent, OnKeyPress>(this);
				m_keyReleaseHandler = new EventHandler<KeyboardInputComponent, OnKeyRelease>(this);
			}

			KeyboardInputComponent::~KeyboardInputComponent()
			{
				SAFE_DELETE(m_keyPressHandler);
				SAFE_DELETE(m_keyReleaseHandler);
			}

			void KeyboardInputComponent::RegisterKeyboardListener(IKeyboardListener* listener)
			{
				m_keyboardListeners.insert(listener);
			}

			void KeyboardInputComponent::UnregisterKeyboardListener(IKeyboardListener* listener)
			{
				m_keyboardListeners.erase(listener);
			}

			bool KeyboardInputComponent::IsKeyPressed(int keyCode) const
			{
				return m_workingKeys.find(keyCode) != m_workingKeys.cend();
			}

			void KeyboardInputComponent::operator()(const OnKeyPress& press)
			{
				m_workingKeys.insert(press.key);

				for (std::set<IKeyboardListener*>::const_iterator ci = m_keyboardListeners.cbegin(); ci != m_keyboardListeners.cend(); ++ci)
				{
					(*ci)->OnKeyPressedHandler(press);
				}
			}

			void KeyboardInputComponent::operator()(const OnKeyRelease& release)
			{
				m_workingKeys.erase(release.key);

				for (std::set<IKeyboardListener*>::const_iterator ci = m_keyboardListeners.cbegin(); ci != m_keyboardListeners.cend(); ++ci)
				{
					(*ci)->OnKeyReleasedHandler(release);
				}
			}
		}
	}
}