#include "InputFacade.h"

namespace PreEngine
{
	namespace Inputs
	{
		InputFacade::InputFacade()
		{
			m_keyboardComponent = new KeyboardInputComponent();
			m_mouseComponent = new MouseInputComponent();
		}

		InputFacade::~InputFacade()
		{
			SAFE_DELETE(m_mouseComponent);
			SAFE_DELETE(m_keyboardComponent);
		}

		void InputFacade::RegisterKeyboardListener(IKeyboardListener* listener)
		{
			m_keyboardComponent->RegisterKeyboardListener(listener);
		}

		void InputFacade::UnregisterKeyboardListener(IKeyboardListener* listener)
		{
			m_keyboardComponent->UnregisterKeyboardListener(listener);
		}

		bool InputFacade::IsKeyPressed(int keyCode) const
		{
			return m_keyboardComponent->IsKeyPressed(keyCode);
		}

		bool InputFacade::IsMouseButtonPressed(int buttonId) const
		{
			return m_mouseComponent->IsMouseButtonPressed(buttonId);
		}

		const OnMouseMove& InputFacade::GetLastMove() const
		{
			return m_mouseComponent->GetLastMove();
		}

		const OnMouseScroll& InputFacade::GetLastScroll() const
		{
			return m_mouseComponent->GetLastScroll();
		}

		void InputFacade::RegisterMouseButtonListener(IMouseButtonListener* listener)
		{
			m_mouseComponent->RegisterMouseButtonListener(listener);
		}

		void InputFacade::UnregisterMouseButtonListener(IMouseButtonListener* listener)
		{
			m_mouseComponent->UnregisterMouseButtonListener(listener);
		}

		void InputFacade::RegisterMouseMoveListener(IMouseMoveListener* listener)
		{
			m_mouseComponent->RegisterMouseMoveListener(listener);
		}

		void InputFacade::UnregisterMouseMoveListener(IMouseMoveListener* listener)
		{
			m_mouseComponent->UnregisterMouseMoveListener(listener);
		}

		void InputFacade::RegisterMouseScrollListener(IMouseScrollListener* listener)
		{
			m_mouseComponent->RegisterMouseScrollListener(listener);
		}

		void InputFacade::UnregisterMouseScrollListener(IMouseScrollListener* listener)
		{
			m_mouseComponent->UnregisterMouseScrollListener(listener);
		}
	}
}