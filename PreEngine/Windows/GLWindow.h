#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include "../Core/Common.h"

#include "../Core/Events/EventChannel.h"
#include "../Core/Events/EventHandler.h"
#include "../Inputs/Core/Keyboards/KeyboardEvents.h"
#include "../Inputs/Core/Mouses/MouseEvents.h"
#include "WindowEvents.h"

#include "MoveDirection.h"
#include "IWindow.h"
#include "GLWindowException.h"
#include "../Core/Engines/Config/EngineConfig.h"
#include "../Core/Engines/Config/SceneItemConfig.h"

namespace PreEngine
{
	namespace Windows
	{
		using namespace PreEngine::Core;
		using namespace PreEngine::Core::Config;
		using namespace PreEngine::Core::Engines::Config;		
		using namespace PreEngine::Utils;
		using namespace PreEngine::Utils::GL;
		using namespace PreEngine::Utils::Log;
		using namespace PreEngine::Core::Events;
		using namespace PreEngine::Windows::Events;
		using namespace PreEngine::Inputs::Core::Keyboards::Events;
		using namespace PreEngine::Inputs::Core::Mouses::Events;
		
		template <class WindowType>
		class GLWindow : public System, public IWindow<WindowType>
		{
		private:
			unsigned int m_sceneId = 0;

			int m_windowPosition = 0;

			unsigned int m_glMajorVersion = 4;

			unsigned int m_glMinorVersion = 2;

			unsigned int m_antialiazingLevel = 4;

			WindowType* m_window = NULL;

			int m_width = 0;

			int m_height = 0;

			int m_topOffset = 0;

			int m_leftOffset = 0;

			int m_normalWidth = 0;

			int m_normalHeight = 0;

			std::string m_title;

			bool m_shouldClose = false;

			bool m_isInFullscreen = false;

			bool m_isFocused = false;

			GLWindow<WindowType>* m_masterWindow = NULL;

			std::vector<IWindow<WindowType>*> m_childWindows;

		private:
			EventHandler<GLWindow<WindowType>, OnResize>* m_resizeHandler;

			EventHandler<GLWindow<WindowType>, OnFocus>* m_focusHandler;

			EventHandler<GLWindow<WindowType>, OnMove>* m_moveHandler;

			EventHandler<GLWindow<WindowType>, ToggleFullscreen>* m_toggleFullscreenHandler;

			EventHandler<GLWindow<WindowType>, OnKeyRelease>* m_keyReleaseHandler;


		public:
			GLWindow(unsigned int sceneId, std::string title, const SceneItemConfig* sceneConfig, const OpenGLConfig* openglConfig, PreEngine::Windows::GLWindow<WindowType>* masterWindow = NULL);

			virtual ~GLWindow();


		private:
			void LoadGLFunctions();

			GLFWwindow* CreateNewWindow(GLFWwindow* master = NULL);

			void MoveWindowToMonitor(GLFWwindow* window, int monitorIndex);

			static void ResizeCallback(GLFWwindow* window, int width, int height);

			static void FocusCallback(GLFWwindow* window, int focused);

			static void ErrorCallback(int errorCode, const char* errorMessage);

		public:
			bool Init();

			void Update(float deltaTime);

			void ShutDown();

		public:
			bool ShouldClose() const;

			unsigned int GetSceneId() const;

			unsigned int GetWindowPosition() const;

			unsigned int GetWidth() const;

			unsigned int GetHeight() const;

			int GetLeftOffset() const;

			int GetTopOffset() const;

			WindowType* GetWindow() const;

			bool IsInFullScreen() const;

			bool IsFocused() const;

			void RefreshWindow();

			void SwapBuffers() const;

			void MoveWindow(MoveDirection direction);

			void MakeWindowContextMain();

			void RegisterChildWindow(IWindow<WindowType>* child);

		public:
			void operator()(const OnResize& resize);

			void operator()(const OnFocus& focus);

			void operator()(const OnMove& move);

			void operator()(const ToggleFullscreen& toggle);

			void operator()(const OnKeyRelease& release);
		};

		template <class WindowType>
		GLWindow<WindowType>::GLWindow(unsigned int sceneId, std::string title, const SceneItemConfig* sceneConfig, const OpenGLConfig* openGLConfig, PreEngine::Windows::GLWindow<WindowType>* masterWindow = NULL)
			: m_sceneId(sceneId), m_title(title), m_masterWindow(masterWindow)
		{
			m_windowPosition = sceneConfig->GetDisplayIndex();
			m_width = sceneConfig->GetWidth();
			m_height = sceneConfig->GetHeight();
			m_topOffset = sceneConfig->GetOffsetTop();
			m_leftOffset = sceneConfig->GetOffsetLeft();

			m_isInFullscreen = sceneConfig->IsFullScreen();

			m_glMajorVersion = openGLConfig->GetMajorVersion(); 
			m_glMinorVersion = openGLConfig->GetMinorVersion();
			m_antialiazingLevel = openGLConfig->GetAntializingLevel();
				
			m_normalWidth = m_width;
			m_normalHeight = m_height;

			m_resizeHandler = new EventHandler<GLWindow<WindowType>, OnResize>(this);
			m_focusHandler = new EventHandler<GLWindow<WindowType>, OnFocus>(this);
			m_toggleFullscreenHandler = new EventHandler<GLWindow<WindowType>, ToggleFullscreen>(this);
			m_moveHandler = new EventHandler<GLWindow<WindowType>, OnMove>(this);
			m_keyReleaseHandler = new EventHandler<GLWindow<WindowType>, OnKeyRelease>(this);

			if (masterWindow == NULL) m_masterWindow = this;
		}

		template <class WindowType>
		GLWindow<WindowType>::~GLWindow()
		{
			SAFE_DELETE(m_keyReleaseHandler);
			SAFE_DELETE(m_moveHandler);
			SAFE_DELETE(m_toggleFullscreenHandler);
			SAFE_DELETE(m_focusHandler);
			SAFE_DELETE(m_resizeHandler);
		}

		template <class WindowType>
		void GLWindow<WindowType>::FocusCallback(GLFWwindow* window, int focused)
		{
			GLWindow<WindowType>* myWindow = (GLWindow<WindowType>*)glfwGetWindowUserPointer(window);
			if (myWindow == NULL) throw new GLWindowException("FocusCallback: Window pointer not set.");

			glfwMakeContextCurrent(window);
			EventChannel::Broadcast(PreEngine::Windows::Events::OnFocus{ myWindow->GetSceneId(), window, focused == GL_TRUE });
		}

		template <class WindowType>
		void GLWindow<WindowType>::ResizeCallback(GLFWwindow* window, int width, int height)
		{
			GLWindow<WindowType>* myWindow = (GLWindow<WindowType>*)glfwGetWindowUserPointer(window);
			if (myWindow == NULL) throw new GLWindowException("ResizeCallback: Window pointer not set.");
			
			glfwMakeContextCurrent(window);
			EventChannel::Broadcast(PreEngine::Windows::Events::OnResize{ myWindow->GetSceneId(), window, width, height });
		}

		template <class WindowType>
		void GLWindow<WindowType>::ErrorCallback(int errorCode, const char* errorMessage)
		{
			Logger::GetInstance().Error() << "Code: " << errorCode << " Message: " << errorMessage;
		}

		template <class WindowType>
		bool GLWindow<WindowType>::Init()
		{
			if (m_masterWindow == this)
			{
#ifdef _DEBUG
				glfwSetErrorCallback(GLWindow<GLFWwindow>::ErrorCallback);
#endif
				if (!glfwInit()) throw new GLWindowException("Could not init glfw.");
			}
			else 
			{
				m_masterWindow->RegisterChildWindow(this);
			}

			m_window = CreateNewWindow(m_masterWindow != NULL ? m_masterWindow->GetWindow() : NULL);
			if (!m_window)
			{
				glfwTerminate();
				throw new GLWindowException("Could not create glfw window.");
			}

			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, &GLWindow<GLFWwindow>::ResizeCallback);
			glfwSetWindowFocusCallback(m_window, &GLWindow<GLFWwindow>::FocusCallback);

			if (m_masterWindow == this)
			{
#ifdef _DEBUG
				GLUtils::InitGLFWDebugMode();
#endif
				MakeWindowContextMain();
				LoadGLFunctions();

				glfwSwapInterval(0);

				Logger::GetInstance().Info() << GLUtils::GetGLInfo() << std::endl;
				Logger::GetInstance().Info() << GLUtils::GetGLExtensionsInfo() << std::endl;
#ifdef _DEBUG
				GLUtils::InitDebugMode();
#endif
				m_channel.Broadcast(PreEngine::Windows::Events::OnCreate{ this });
			}

			MoveWindowToMonitor(m_window, m_windowPosition);

			m_channel.Broadcast(PreEngine::Windows::Events::OnResize{ m_sceneId, m_window, m_width, m_height });
			return true;
		}

		template <class WindowType>
		void GLWindow<WindowType>::Update(float deltaTime)
		{
		}

		template <class WindowType>
		void GLWindow<WindowType>::ShutDown()
		{
			m_channel.Broadcast(PreEngine::Windows::Events::OnClose{ this });

			glfwDestroyWindow(m_window);
			glfwTerminate();
		}

		template <class WindowType>
		void GLWindow<WindowType>::LoadGLFunctions()
		{
			int loaded = ogl_LoadFunctions();
			if (loaded == ogl_LOAD_FAILED)
			{
				throw new GLWindowException("Could not load GL functions.");
			}
		}

		template <class WindowType>
		GLFWwindow* GLWindow<WindowType>::CreateNewWindow(GLFWwindow* master)
		{
			GLFWwindow* window = NULL;
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glMajorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glMinorVersion);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#ifdef _DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
			glfwWindowHint(GLFW_SAMPLES, m_antialiazingLevel);

			if (m_isInFullscreen)
			{
				glfwWindowHint(GLFW_DECORATED, GL_FALSE);

				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				if (master != NULL)
				{
					int count;
					GLFWmonitor** monitors = glfwGetMonitors(&count);
					if (count > (int)m_sceneId) monitor = monitors[m_sceneId];
				}

				const GLFWvidmode* mode = glfwGetVideoMode(monitor); // hack !!!
				m_width = mode->width;
				m_height = mode->height;
				window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL/*monitor*/, master);
			}
			else
			{
				glfwWindowHint(GLFW_DECORATED, GL_TRUE);

				m_width = m_normalWidth;
				m_height = m_normalHeight;
				window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, master);
			}

			return window;
		}

		template <class WindowType>
		void GLWindow<WindowType>::MoveWindowToMonitor(GLFWwindow* window, int monitorIndex)
		{
			int xPositon = 0, yPosition = 0;
			int windowWidth = 0, windowHeight = 0;

			int countOfMonitors;
			GLFWmonitor** monitors = glfwGetMonitors(&countOfMonitors);
			if (monitors == NULL || countOfMonitors <= 0) throw new GLWindowException("No monitors connected?!.");

			if (monitorIndex >= countOfMonitors) monitorIndex = countOfMonitors - 1;

			const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitorIndex]);
			windowWidth = mode->width;
			windowHeight = mode->height;

			glfwGetMonitorPos(monitors[monitorIndex], &xPositon, &yPosition);

			if (m_isInFullscreen)
			{
				glfwSetWindowPos(window, xPositon, yPosition);
				glfwSetWindowSize(window, windowWidth, windowHeight);
			}
			else
			{
				glfwSetWindowPos(window, xPositon + m_leftOffset, yPosition + m_topOffset);
			}
		}

		template <class WindowType>
		void GLWindow<WindowType>::MoveWindow(PreEngine::Windows::MoveDirection direction)
		{
			int countOfMonitors;
			GLFWmonitor** monitors = glfwGetMonitors(&countOfMonitors);

			if (direction == PreEngine::Windows::MoveDirection::LEFT)
			{
				m_windowPosition = (m_windowPosition > 0) ? --m_windowPosition : countOfMonitors - 1;
			}
			else
			{
				m_windowPosition = (m_windowPosition + 1 >= countOfMonitors) ? 0 : ++m_windowPosition;
			}

			MoveWindowToMonitor(m_window, m_windowPosition);
		}

		template <class WindowType>
		void GLWindow<WindowType>::RefreshWindow()
		{
			GLFWwindow* window = CreateNewWindow(m_masterWindow->GetWindow());
			glfwDestroyWindow(m_window);
			m_window = window;
			MakeWindowContextMain();

			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, &GLWindow<GLFWwindow>::ResizeCallback);

			if (m_masterWindow == this) m_channel.Broadcast(PreEngine::Windows::Events::OnCreate{ this });

			MoveWindowToMonitor(m_window, m_windowPosition);

			m_channel.Broadcast(PreEngine::Windows::Events::OnResize{ m_sceneId, m_window, m_width, m_height });
			m_channel.Broadcast(PreEngine::Windows::Events::OnReset{ m_sceneId, this });
		}

		template <class WindowType>
		void GLWindow<WindowType>::SwapBuffers() const
		{
			glfwSwapBuffers(m_window);
		}

		template <class WindowType>
		void GLWindow<WindowType>::MakeWindowContextMain()
		{
			glfwMakeContextCurrent(m_window);
		}

		template <class WindowType>
		void GLWindow<WindowType>::RegisterChildWindow(IWindow<WindowType>* child)
		{
			m_childWindows.push_back(child);
		}

		template <class WindowType>
		bool GLWindow<WindowType>::ShouldClose() const
		{
			return glfwWindowShouldClose(m_window) || m_shouldClose;
		}

		template <class WindowType>
		unsigned int GLWindow<WindowType>::GetWidth() const
		{
			return m_width;
		}

		template <class WindowType>
		unsigned int GLWindow<WindowType>::GetHeight() const
		{
			return m_height;
		}

		template <class WindowType>
		int GLWindow<WindowType>::GetLeftOffset() const
		{
			return m_leftOffset;
		}

		template <class WindowType>
		int GLWindow<WindowType>::GetTopOffset() const
		{
			return m_topOffset;
		}

		template <class WindowType>
		unsigned int GLWindow<WindowType>::GetSceneId() const
		{
			return m_sceneId;
		}

		template <class WindowType>
		unsigned int GLWindow<WindowType>::GetWindowPosition() const
		{
			return m_windowPosition;
		}

		template <class WindowType>
		WindowType* GLWindow<WindowType>::GetWindow() const
		{
			return m_window;
		}

		template <class WindowType>
		bool GLWindow<WindowType>::IsInFullScreen() const
		{
			return m_isInFullscreen;
		}

		template <class WindowType>
		bool GLWindow<WindowType>::IsFocused() const 
		{
			return m_isFocused;
		}

		template <class WindowType>
		void GLWindow<WindowType>::operator()(const OnFocus& focus)
		{
			m_isFocused = m_window == focus.window ? focus.isFocused : false;
		}

		template <class WindowType>
		void GLWindow<WindowType>::operator()(const OnResize& resize)
		{
			if (m_sceneId == resize.sceneId && resize.height > 0 && resize.width > 0)
			{
				m_width = resize.width;
				m_height = resize.height;
			}
		}

		template <class WindowType>
		void GLWindow<WindowType>::operator()(const ToggleFullscreen& toggle)
		{
			m_masterWindow = toggle.window;
			m_isInFullscreen = toggle.fullScreen;
			RefreshWindow();
		}

		template <class WindowType>
		void GLWindow<WindowType>::operator()(const OnMove& move)
		{
			if (m_sceneId != move.sceneId) return;

			MoveWindow(move.direction);
		}

		template <class WindowType>
		void GLWindow<WindowType>::operator()(const OnKeyRelease& release)
		{
			if (release.key == GLFW_KEY_ESCAPE) m_shouldClose = true;

			if (m_masterWindow != this) return;
			
			if (release.key == GLFW_KEY_F) m_channel.Broadcast(PreEngine::Windows::Events::ToggleFullscreen{ m_sceneId, this, !m_isInFullscreen });

			if (release.key >= GLFW_KEY_F1 && release.key <= GLFW_KEY_F25)
			{
				int baseCode = release.key - GLFW_KEY_F1;
				MoveDirection direction = baseCode % 2 == 0 ? PreEngine::Windows::MoveDirection::LEFT : PreEngine::Windows::MoveDirection::RIGHT;
				unsigned int sceneId = baseCode / 2;
				m_channel.Broadcast(PreEngine::Windows::Events::OnMove{ sceneId, this, direction });
			}

			/*if (release.key == GLFW_KEY_F1 || release.key == GLFW_KEY_F2)
			{
				GLWindow<WindowType>* focusedWindow = NULL;

				if (!m_isFocused)
				{
					for (std::vector<GLWindow<WindowType>*>::iterator ii = m_childWindows.begin(); ii != m_childWindows.end(); ++ii)
					{
						GLWindow<WindowType>* window = (*ii);
						if (window->IsFocused())
						{
							focusedWindow = window;
							break;
						}
					}
				}
				else
				{
					focusedWindow = this;
				}

				if (focusedWindow != NULL)
				{
					if (release.key == GLFW_KEY_F1) m_channel.Broadcast(PreEngine::Core::Messages::Window::OnMove{ focusedWindow->GetSceneId(), this, PreEngine::Windows::MoveDirection::LEFT });
					if (release.key == GLFW_KEY_F2) m_channel.Broadcast(PreEngine::Core::Messages::Window::OnMove{ focusedWindow->GetSceneId(), this, PreEngine::Windows::MoveDirection::RIGHT });
				}
			}*/			
		}
	}
}

#endif