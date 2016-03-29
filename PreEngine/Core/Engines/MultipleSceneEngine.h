#ifndef MULTIPLE_SCENE_ENGINE_H
#define MULTIPLE_SCENE_ENGINE_H

#include "AbstractEngine.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			using namespace PreEngine::Utils::GL;

			template<class RootType>
			class MultipleSceneEngine : public AbstractEngine
			{
			private:
				IScene<RootType>* m_mainScene;

				PreEngine::Windows::GLWindow<GLFWwindow>* m_mainWindow;

				std::vector<PreEngine::Windows::IWindow<GLFWwindow>*> m_windows;

				std::vector<IScene<RootType>*> m_scenes;

			public:
				MultipleSceneEngine(EngineConfig* config);

				virtual ~MultipleSceneEngine();

			public:
				void Init();

				void MainLoop();

				void ShutDown();

			public:
				PreEngine::Windows::IWindow<GLFWwindow>* GetMainWindow() const;

				IScene<RootType>* GetMainScene() const;

				PreEngine::Windows::IWindow<GLFWwindow>* GetWindow(unsigned int index) const;

				IScene<RootType>* GetScene(unsigned int index) const;
			};


			template<class RootType>
			MultipleSceneEngine<RootType>::MultipleSceneEngine(EngineConfig* config)
				: AbstractEngine(config)
			{
				std::vector<SceneItemConfig*> scenes = config->GetSceneItems();
				for (unsigned int i = 0; i < scenes.size(); i++)
				{
					SceneItemConfig* sceneConfig = scenes[i];
					std::string windowTitle(config->GetWindowTitle() + " (" + (i == 0 ? "Master" : "Slave " + std::to_string(i)) + ") ");

					PreEngine::Windows::GLWindow<GLFWwindow>* window = new PreEngine::Windows::GLWindow<GLFWwindow>(i, windowTitle, sceneConfig, config->GetOpenGLConfig(), m_mainWindow);
					if (i == 0)	m_mainWindow = window;
					m_windows.push_back(window);

					IScene<RootType>* scene = NULL;
					if (sceneConfig->GetSceneLayout() == SceneLayout::SINGLE) scene = new Scene<RootType>(i, sceneConfig);
					else scene = new DoubleScene<RootType>(i, sceneConfig);

					if (i == 0) m_mainScene = scene;
					m_scenes.push_back(scene);
				}
			}

			template<class RootType>
			MultipleSceneEngine<RootType>::~MultipleSceneEngine()
			{
				for (std::vector<IScene<RootType>*>::iterator ii = m_scenes.begin(); ii != m_scenes.end(); ++ii)
				{
					SAFE_DELETE(*ii);
				}

				for (std::vector<PreEngine::Windows::IWindow<GLFWwindow>*>::iterator ii = m_windows.begin(); ii != m_windows.end(); ++ii)
				{
					SAFE_DELETE(*ii);
				}
			}

			template<class RootType>
			void MultipleSceneEngine<RootType>::Init()
			{
				EventChannel::Broadcast(Core::OnEnginePreInit{});

				m_input->Init();
				m_audioContext->Init();

				for (unsigned int i = 0; i < m_windows.size(); i++)
				{
					m_windows[i]->Init();
					m_windows[i]->MakeWindowContextMain();
					m_scenes[i]->Init();
				}

				m_mainWindow->MakeWindowContextMain();				

				EventChannel::Broadcast(Core::OnEnginePostInit{});
			}

			template<class RootType>
			void MultipleSceneEngine<RootType>::MainLoop()
			{
				EventChannel::Broadcast(Core::OnEngineMainLoopStart{});

				m_clock->Reset();

				float deltaTime = 0.0f;
				bool shouldSwitchContext = m_windows.size() > 1;
				while (!m_mainWindow->ShouldClose())
				{
					GLUtils::CheckForOpenGLError(__FILE__, __LINE__);

					m_clock->UpdateClock();
					deltaTime += m_clock->GetDelta();

					if (deltaTime >= FIXED_FRAME_PERIOD || m_unlimitedLoop)
					{
						m_input->Update(deltaTime);

						for (unsigned int i = 0; i < m_windows.size(); i++)
						{
							if (shouldSwitchContext) m_windows[i]->MakeWindowContextMain();

							m_scenes[i]->Update(deltaTime);
							m_scenes[i]->Render();
							m_windows[i]->SwapBuffers();
						}

						deltaTime = 0.0f;
					}

					glfwPollEvents();
				}

				EventChannel::Broadcast(Core::OnEngineMainLoopFinish{});
			}

			template<class RootType>
			void MultipleSceneEngine<RootType>::ShutDown()
			{
				for (std::vector<IScene<RootType>*>::iterator ii = m_scenes.begin(); ii != m_scenes.end(); ++ii)
				{
					(*ii)->ShutDown();
				}

				for (std::vector<PreEngine::Windows::IWindow<GLFWwindow>*>::reverse_iterator ii = m_windows.rbegin(); ii != m_windows.rend(); ++ii)
				{
					(*ii)->ShutDown();
				}

				m_audioContext->ShutDown();
				m_input->ShutDown();
			}

			template<class RootType>
			IScene<RootType>* MultipleSceneEngine<RootType>::GetMainScene() const
			{
				return m_mainScene;
			}

			template<class RootType>
			PreEngine::Windows::IWindow<GLFWwindow>* MultipleSceneEngine<RootType>::GetMainWindow() const
			{
				return m_mainWindow;
			}

			template<class RootType>
			PreEngine::Windows::IWindow<GLFWwindow>* MultipleSceneEngine<RootType>::GetWindow(unsigned int index) const
			{
				if (index >= 0 && index < m_windows.size())
				{
					return m_windows[index];
				}
				else
				{
					throw EngineException("Could not get non existing window at index " + index);
				}
			}

			template<class RootType>
			IScene<RootType>* MultipleSceneEngine<RootType>::GetScene(unsigned int index) const
			{
				if (index >= 0 && index < m_scenes.size())
				{
					return m_scenes[index];
				}
				else
				{
					throw EngineException("Could not get non existing scene at index " + index);
				}
			}
		}
	}
}

#endif