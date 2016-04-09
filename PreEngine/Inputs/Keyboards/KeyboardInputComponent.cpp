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
				std::lock_guard<std::mutex> lock(m_mutex);
				m_keyboardListeners.insert(listener);
			}

			void KeyboardInputComponent::UnregisterKeyboardListener(IKeyboardListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);				
				auto it = std::find(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener);
				if (it != m_keyboardListeners.end()) m_keyboardListeners.erase(it);
			}

			bool KeyboardInputComponent::IsKeyboardListenerRegistered(IKeyboardListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				return m_keyboardListeners.find(listener) != m_keyboardListeners.cend();
			}

			bool KeyboardInputComponent::IsKeyPressed(int keyCode)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				return m_workingKeys.find(keyCode) != m_workingKeys.cend();
			}

			void KeyboardInputComponent::operator()(const OnKeyPress& press)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_workingKeys.insert(press.key);

				for (std::set<IKeyboardListener*>::const_iterator ci = m_keyboardListeners.cbegin(); ci != m_keyboardListeners.cend(); ++ci)
				{
					(*ci)->OnKeyPressedHandler(press);
				}
			}

			void KeyboardInputComponent::operator()(const OnKeyRelease& release)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_workingKeys.erase(release.key);

				for (std::set<IKeyboardListener*>::const_iterator ci = m_keyboardListeners.cbegin(); ci != m_keyboardListeners.cend(); ++ci)
				{
					(*ci)->OnKeyReleasedHandler(release);
				}
			}
		}
	}
}