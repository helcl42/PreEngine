#ifndef WINDOW_MESSAGES_H
#define WINDOW_MESSAGES_H

#include "../Core/Common.h"
#include "../Core/Events/BaseEvent.h"

#include "MoveDirection.h"

namespace PreEngine
{
	namespace Windows
	{
		template <class WindowType> class GLWindow;
	}
}

namespace PreEngine
{
	namespace Windows
	{
		namespace Events
		{
			using namespace PreEngine::Windows;
			using namespace PreEngine::Core::Events;

			struct OnCreate : BaseEvent
			{
				GLWindow<GLFWwindow>* window;


				OnCreate() {}

				OnCreate(GLWindow<GLFWwindow>* window)
					: window(window)
				{
				}

				virtual ~OnCreate()
				{
				}
			};


			struct OnFocus : BaseEvent
			{				
				GLFWwindow* window;

				unsigned int sceneId;

				bool isFocused;

				OnFocus() {}

				OnFocus(unsigned int sceneId, GLFWwindow* window, bool focused)
					: sceneId(sceneId), window(window), isFocused(focused)
				{
				}

				virtual ~OnFocus()
				{
				}
			};

			struct OnResize : BaseEvent
			{
				GLFWwindow* window;

				unsigned int sceneId;

				int width;

				int height;


				OnResize() {}

				OnResize(unsigned int sceneId, GLFWwindow* window, int width, int height)
					: sceneId(sceneId), window(window), width(width), height(height)
				{
				}

				virtual ~OnResize()
				{
				}
			};

			struct OnMove : BaseEvent
			{
				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;

				PreEngine::Windows::MoveDirection direction;


				OnMove() {}

				OnMove(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window, enum PreEngine::Windows::MoveDirection direction)
					: sceneId(sceneId), window(window), direction(direction)
				{
				}

				virtual ~OnMove()
				{
				}
			};


			struct ToggleFullscreen : BaseEvent
			{
				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;

				bool fullScreen;


				ToggleFullscreen() {}

				ToggleFullscreen(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window, bool fullScreen)
					: sceneId(sceneId), window(window), fullScreen(fullScreen)
				{
				}

				virtual ~ToggleFullscreen()
				{
				}
			};


			struct OnReset : BaseEvent
			{
				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;


				OnReset() {}

				OnReset(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window)
					: sceneId(sceneId), window(window)
				{
				}

				virtual ~OnReset()
				{
				}
			};


			struct OnClose : BaseEvent
			{
				PreEngine::Windows::GLWindow<GLFWwindow>* window;


				OnClose() {}

				OnClose(PreEngine::Windows::GLWindow<GLFWwindow>* window)
					: window(window)
				{
				}

				virtual ~OnClose()
				{
				}
			};
		}
	}
}

#endif