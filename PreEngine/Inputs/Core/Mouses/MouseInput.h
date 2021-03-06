#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include "../../../Core/System.h"
#include "../../../Windows/GLWindow.h"
#include "../../../Core/Events/EventChannel.h"
#include "../../../Core/System.h"

#include "MouseEvents.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Mouses
			{
				using namespace PreEngine::Core;
				using namespace PreEngine::Core::Events;
				using namespace PreEngine::Inputs::Core::Mouses::Events;

				class MouseInput : public System
				{
				private:
					PreEngine::Windows::IWindow<GLFWwindow>* m_window;

					glm::dvec2 m_actualMousePosition;

					glm::dvec2 m_actualMousePositionAbsolute;

					EventHandler<MouseInput, OnMouseLockRequest> m_mouseLockRequestHandler{ this };

					EventHandler<MouseInput, OnMouseShowRequest> m_mouseShowRequestHandler{ this };

					bool m_mouseLockEnabled = true;

					const double MIN_MOUSE_DELTA = 1.0;

				private:
					static void MouseScrollCallback(GLFWwindow* window, double xPos, double yPos);

					static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

				public:
					MouseInput(PreEngine::Windows::IWindow<GLFWwindow>* window);

					virtual ~MouseInput();

				public:
					bool Init();

					void Update(float deltaTime);

					void ShutDown();

				public:
					void operator()(const OnMouseLockRequest& lockRequest);

					void operator()(const OnMouseShowRequest& showRequest);
				};
			}
		}
	}
}

#endif