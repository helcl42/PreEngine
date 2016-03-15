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
				std::string message;

				GLWindow<GLFWwindow>* window;


				OnCreate() {}

				OnCreate(GLWindow<GLFWwindow>* window)
					: window(window)
				{
					message = std::string("Hey I'm created window.");
				}

				virtual ~OnCreate()
				{
				}
			};


			struct OnFocus : BaseEvent
			{
				std::string message;

				GLFWwindow* window;

				unsigned int sceneId;

				bool isFocused;

				OnFocus() {}

				OnFocus(unsigned int sceneId, GLFWwindow* window, bool focused)
					: sceneId(sceneId), window(window), isFocused(focused)
				{
					message = std::string("Hey I focus window.");
				}

				virtual ~OnFocus()
				{
				}
			};

			struct OnResize : BaseEvent
			{
				std::string message;

				GLFWwindow* window;

				unsigned int sceneId;

				int width;

				int height;


				OnResize() {}

				OnResize(unsigned int sceneId, GLFWwindow* window, int width, int height)
					: sceneId(sceneId), window(window), width(width), height(height)
				{
					message = std::string("Hey I'm resizing window.");
				}

				virtual ~OnResize()
				{
				}
			};

			struct OnMove : BaseEvent
			{
				std::string message;

				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;

				PreEngine::Windows::MoveDirection direction;


				OnMove() {}

				OnMove(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window, enum PreEngine::Windows::MoveDirection direction)
					: sceneId(sceneId), window(window), direction(direction)
				{
					message = std::string("Hey I'm moving window window.");
				}

				virtual ~OnMove()
				{
				}
			};


			struct ToggleFullscreen : BaseEvent
			{
				std::string message;

				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;

				bool fullScreen;


				ToggleFullscreen() {}

				ToggleFullscreen(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window, bool fullScreen)
					: sceneId(sceneId), window(window), fullScreen(fullScreen)
				{
					message = std::string("Hey I toggle to/from fullscreen");
				}

				virtual ~ToggleFullscreen()
				{
				}
			};


			struct OnReset : BaseEvent
			{
				std::string message;

				PreEngine::Windows::GLWindow<GLFWwindow>* window;

				unsigned int sceneId;


				OnReset() {}

				OnReset(unsigned int sceneId, PreEngine::Windows::GLWindow<GLFWwindow>* window)
					: sceneId(sceneId), window(window)
				{
					message = std::string("Hey I'm reseting window.");
				}

				virtual ~OnReset()
				{
				}
			};


			struct OnClose : BaseEvent
			{
				std::string message;

				PreEngine::Windows::GLWindow<GLFWwindow>* window;


				OnClose() {}

				OnClose(PreEngine::Windows::GLWindow<GLFWwindow>* window)
					: window(window)
				{
					message = std::string("Hey I'm closing window :(");
				}

				virtual ~OnClose()
				{
				}
			};
		}
	}
}

#endif