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

				EventHandler<MouseInputComponent, OnMouseButtonPress>* m_mouseButtonPressHandler;

				EventHandler<MouseInputComponent, OnMouseButtonRelease>* m_mouseButtonReleaseHandler;

				EventHandler<MouseInputComponent, OnMouseMove>* m_mouseMoveHandler;

				EventHandler<MouseInputComponent, OnMouseScroll>* m_mouseScrollHandler;

				OnMouseMove m_lastMove;

				OnMouseScroll m_lastScroll;

				std::set<IMouseMoveListener*> m_mouseMoveListeners;

				std::set<IMouseButtonListener*> m_mouseButtonListeners;

				std::set<IMouseScrollListener*> m_mouseScrollListeners;

			public:
				MouseInputComponent();

				virtual ~MouseInputComponent();

			public:
				bool IsMouseButtonPressed(int buttonId);

				const OnMouseMove& GetLastMove() const;

				const OnMouseScroll& GetLastScroll() const;

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