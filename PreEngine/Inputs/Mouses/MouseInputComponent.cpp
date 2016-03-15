#include "MouseInputComponent.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Mouses
		{
			MouseInputComponent::MouseInputComponent()
			{
				m_mouseButtonPressHandler = new EventHandler<MouseInputComponent, OnMouseButtonPress>(this);
				m_mouseButtonReleaseHandler = new EventHandler<MouseInputComponent, OnMouseButtonRelease>(this);
				m_mouseMoveHandler = new EventHandler<MouseInputComponent, OnMouseMove>(this);
				m_mouseScrollHandler = new EventHandler<MouseInputComponent, OnMouseScroll>(this);
			}

			MouseInputComponent::~MouseInputComponent()
			{
				SAFE_DELETE(m_mouseScrollHandler);
				SAFE_DELETE(m_mouseMoveHandler);
				SAFE_DELETE(m_mouseButtonPressHandler);
				SAFE_DELETE(m_mouseButtonReleaseHandler);
			}

			bool MouseInputComponent::IsMouseButtonPressed(int buttonId) const
			{
				return m_workingButtons.find(buttonId) != m_workingButtons.cend();
			}

			const OnMouseMove& MouseInputComponent::GetLastMove() const
			{
				return m_lastMove;
			}

			const OnMouseScroll& MouseInputComponent::GetLastScroll() const
			{
				return m_lastScroll;
			}

			void MouseInputComponent::RegisterMouseButtonListener(IMouseButtonListener* listener)
			{
				m_mouseButtonListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseButtonListener(IMouseButtonListener* listener)
			{
				m_mouseButtonListeners.erase(listener);
			}

			void MouseInputComponent::RegisterMouseMoveListener(IMouseMoveListener* listener)
			{
				m_mouseMoveListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseMoveListener(IMouseMoveListener* listener)
			{
				m_mouseMoveListeners.erase(listener);
			}

			void MouseInputComponent::RegisterMouseScrollListener(IMouseScrollListener* listener)
			{
				m_mouseScrollListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseScrollListener(IMouseScrollListener* listener)
			{
				m_mouseScrollListeners.erase(listener);
			}

			void MouseInputComponent::operator()(const OnMouseButtonPress& press)
			{
				m_workingButtons.insert(press.button);

				for (std::set<IMouseButtonListener*>::const_iterator ci = m_mouseButtonListeners.cbegin(); ci != m_mouseButtonListeners.cend(); ++ci)
				{
					(*ci)->OnMouseButtonPressedHandler(press);
				}
			}

			void MouseInputComponent::operator()(const OnMouseButtonRelease& release)
			{
				m_workingButtons.erase(release.button);

				for (std::set<IMouseButtonListener*>::const_iterator ci = m_mouseButtonListeners.cbegin(); ci != m_mouseButtonListeners.cend(); ++ci)
				{
					(*ci)->OnMouseButtonReleasedHandler(release);
				}
			}

			void MouseInputComponent::operator()(const OnMouseMove& move)
			{
				//std::cout << "MOVE: A: [" << move.actualPosition.x << "," << move.actualPosition.y << "]" << " P: [" << move.previousPosition.x << "," << move.previousPosition.y << "]" << " DIFF: [" << move.diff.x << "," << move.diff.y << "]" << std::endl;
				m_lastMove = move;

				for (std::set<IMouseMoveListener*>::const_iterator ci = m_mouseMoveListeners.cbegin(); ci != m_mouseMoveListeners.cend(); ++ci)
				{
					(*ci)->OnMouseMoveHandler(move);
				}
			}

			void MouseInputComponent::operator()(const OnMouseScroll& scroll)
			{
				//std::cout << "SCROLL: " << " DIFF: [" << scroll.diff.x << "," << scroll.diff.y << "]" << std::endl;
				m_lastScroll = scroll;

				for (std::set<IMouseScrollListener*>::const_iterator ci = m_mouseScrollListeners.cbegin(); ci != m_mouseScrollListeners.cend(); ++ci)
				{
					(*ci)->OnMouseScrollHandler(scroll);
				}
			}
		}
	}
}