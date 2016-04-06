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

			bool MouseInputComponent::IsMouseButtonPressed(int buttonId)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
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
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseButtonListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseButtonListener(IMouseButtonListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseButtonListeners.erase(listener);
			}

			bool MouseInputComponent::IsMouseButtonListenerRegistered(IMouseButtonListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				return m_mouseButtonListeners.find(listener) != m_mouseButtonListeners.cend();
			}

			void MouseInputComponent::RegisterMouseMoveListener(IMouseMoveListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseMoveListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseMoveListener(IMouseMoveListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseMoveListeners.erase(listener);
			}

			bool MouseInputComponent::IsMouseMoveListenerRegistered(IMouseMoveListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				return m_mouseMoveListeners.find(listener) != m_mouseMoveListeners.cend();
			}

			void MouseInputComponent::RegisterMouseScrollListener(IMouseScrollListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseScrollListeners.insert(listener);
			}

			void MouseInputComponent::UnregisterMouseScrollListener(IMouseScrollListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_mouseScrollListeners.erase(listener);
			}

			bool MouseInputComponent::IsMouseScrollListenerRegistered(IMouseScrollListener* listener)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				return m_mouseScrollListeners.find(listener) != m_mouseScrollListeners.cend();
			}

			void MouseInputComponent::operator()(const OnMouseButtonPress& press)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_workingButtons.insert(press.button);

				for (std::set<IMouseButtonListener*>::const_iterator ci = m_mouseButtonListeners.cbegin(); ci != m_mouseButtonListeners.cend(); ++ci)
				{
					(*ci)->OnMouseButtonPressedHandler(press);
				}
			}

			void MouseInputComponent::operator()(const OnMouseButtonRelease& release)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_workingButtons.erase(release.button);

				for (std::set<IMouseButtonListener*>::const_iterator ci = m_mouseButtonListeners.cbegin(); ci != m_mouseButtonListeners.cend(); ++ci)
				{
					(*ci)->OnMouseButtonReleasedHandler(release);
				}
			}

			void MouseInputComponent::operator()(const OnMouseMove& move)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_lastMove = move;

				for (std::set<IMouseMoveListener*>::const_iterator ci = m_mouseMoveListeners.cbegin(); ci != m_mouseMoveListeners.cend(); ++ci)
				{
					(*ci)->OnMouseMoveHandler(move);
				}
			}

			void MouseInputComponent::operator()(const OnMouseScroll& scroll)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_lastScroll = scroll;

				for (std::set<IMouseScrollListener*>::const_iterator ci = m_mouseScrollListeners.cbegin(); ci != m_mouseScrollListeners.cend(); ++ci)
				{
					(*ci)->OnMouseScrollHandler(scroll);
				}
			}
		}
	}
}