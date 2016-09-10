#ifndef IINPUT_FACADE_H
#define IINPUT_FACADE_H

#include "Mouses/IMouseButtonListener.h"
#include "Mouses/IMouseMoveListener.h"
#include "Mouses/IMouseScrollListener.h"
#include "Keyboards/IKeyboardListener.h"

namespace PreEngine
{
	namespace Inputs
	{
		using namespace PreEngine::Inputs::Core::Keyboards::Events;
		using namespace PreEngine::Inputs::Core::Mouses::Events;

		using namespace PreEngine::Inputs::Keyboards;
		using namespace PreEngine::Inputs::Mouses;

		class IInputFacade
		{
		public:
			virtual void RegisterKeyboardListener(IKeyboardListener* listener) = 0;

			virtual void UnregisterKeyboardListener(IKeyboardListener* listener) = 0;

			virtual bool IsKeyboardListenerRegistered(IKeyboardListener* listener) = 0;

			virtual bool IsKeyPressed(int keyCode) const = 0;

			virtual bool IsMouseButtonPressed(int buttonId) const = 0;

			virtual const OnMouseMove& GetLastMove() const = 0;

			virtual const OnMouseScroll& GetLastScroll() const = 0;

			virtual void ShowCursor(bool show) = 0;

			virtual bool IsCursorShown() const = 0;

			virtual void LockMouse(bool lock) = 0;

			virtual bool IsMouseLocked() const = 0;

			virtual void RegisterMouseButtonListener(IMouseButtonListener* listener) = 0;

			virtual void UnregisterMouseButtonListener(IMouseButtonListener* listener) = 0;

			virtual void RegisterMouseMoveListener(IMouseMoveListener* listener) = 0;

			virtual void UnregisterMouseMoveListener(IMouseMoveListener* listener) = 0;

			virtual void RegisterMouseScrollListener(IMouseScrollListener* listener) = 0;

			virtual void UnregisterMouseScrollListener(IMouseScrollListener* listener) = 0;

		public:
			virtual ~IInputFacade() {}
		};

	}
}

#endif