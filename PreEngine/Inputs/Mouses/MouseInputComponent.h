#ifndef IMOUSE_INPUT_COMPONENT_H
#define IMOUSE_INPUT_COMPONENT_H

#include "../../Core/Common.h"
#include "../../Core/Events/EventHandler.h"
#include "../Core/Mouses/MouseEvents.h"

#include "IMouseButtonListener.h"
#include "IMouseMoveListener.h"
#include "IMouseScrollListener.h"
#include "../AbstractInputComponent.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Mouses
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class MouseInputComponent : public AbstractInputComponent
			{
			private:
				std::set<int> m_workingButtons;

				EventHandler<MouseInputComponent, OnMouseButtonPress> m_mouseButtonPressHandler{ this };

				EventHandler<MouseInputComponent, OnMouseButtonRelease> m_mouseButtonReleaseHandler{ this };

				EventHandler<MouseInputComponent, OnMouseMove> m_mouseMoveHandler{ this };

				EventHandler<MouseInputComponent, OnMouseScroll> m_mouseScrollHandler{ this };

				OnMouseMove m_lastMove;

				OnMouseScroll m_lastScroll;

				std::set<IMouseMoveListener*> m_mouseMoveListeners;

				std::set<IMouseButtonListener*> m_mouseButtonListeners;

				std::set<IMouseScrollListener*> m_mouseScrollListeners;

				bool m_cursorShown = false;

				bool m_mouseLocked = true;

			public:
				MouseInputComponent();

				virtual ~MouseInputComponent();

			public:
				bool IsMouseButtonPressed(int buttonId);

				const OnMouseMove& GetLastMove() const;

				const OnMouseScroll& GetLastScroll() const;

				void ShowCursor(bool show);

				bool IsCursorShown() const;

				void LockMouse(bool lock);

				bool IsMouseLocked() const;

				void RegisterMouseButtonListener(IMouseButtonListener* listener);

				void UnregisterMouseButtonListener(IMouseButtonListener* listener);

				bool IsMouseButtonListenerRegistered(IMouseButtonListener* listener);

				void RegisterMouseMoveListener(IMouseMoveListener* listener);

				void UnregisterMouseMoveListener(IMouseMoveListener* listener);

				bool IsMouseMoveListenerRegistered(IMouseMoveListener* listener);

				void RegisterMouseScrollListener(IMouseScrollListener* listener);

				void UnregisterMouseScrollListener(IMouseScrollListener* listener);

				bool IsMouseScrollListenerRegistered(IMouseScrollListener* listener);

			public:
				void operator()(const OnMouseButtonPress& press);

				void operator()(const OnMouseButtonRelease& release);

				void operator()(const OnMouseMove& move);

				void operator()(const OnMouseScroll& scroll);
			};
		}
	}
}

#endif