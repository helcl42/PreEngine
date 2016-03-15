#ifndef INPUT_FACADE_H
#define INPUT_FACADE_H

#include "IInputFacade.h"
#include "Mouses/MouseInputComponent.h"
#include "Keyboards/KeyboardInputComponent.h"

namespace PreEngine
{
	namespace Inputs
	{
		using namespace PreEngine::Inputs::Keyboards;
		using namespace PreEngine::Inputs::Mouses;

		class InputFacade : public IInputFacade
		{
		private:
			KeyboardInputComponent* m_keyboardComponent;

			MouseInputComponent* m_mouseComponent;

		public:
			InputFacade();

			virtual ~InputFacade();

		public:
			void RegisterKeyboardListener(IKeyboardListener* listener);

			void UnregisterKeyboardListener(IKeyboardListener* listener);

			bool IsKeyPressed(int keyCode) const;

			bool IsMouseButtonPressed(int buttonId) const;

			const OnMouseMove& GetLastMove() const;

			const OnMouseScroll& GetLastScroll() const;

			void RegisterMouseButtonListener(IMouseButtonListener* listener);

			void UnregisterMouseButtonListener(IMouseButtonListener* listener);

			void RegisterMouseMoveListener(IMouseMoveListener* listener);

			void UnregisterMouseMoveListener(IMouseMoveListener* listener);

			void RegisterMouseScrollListener(IMouseScrollListener* listener);

			void UnregisterMouseScrollListener(IMouseScrollListener* listener);
		};
	}
}

#endif