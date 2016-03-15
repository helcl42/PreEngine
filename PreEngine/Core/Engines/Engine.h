#ifndef ENGINE_H
#define ENGINE_H

#include "AbstractEngine.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			using namespace PreEngine::Windows;
			using namespace PreEngine::Utils::GL;

			template<class RootType>
			class Engine : public AbstractEngine
			{
			private:
				IScene<RootType>* m_scene;

				PreEngine::Windows::GLWindow<GLFWwindow>* m_window;

			public:
				Engine(EngineConfig* config);

				virtual ~Engine();

			public:
				void Init();

				void MainLoop();

				void ShutDown();

			public:
				IScene<RootType>* GetScene() const;

				PreEngine::Windows::IWindow<GLFWwindow>* GetWindow() const;
			};

			template<class RootType>
			Engine<RootType>::Engine(EngineConfig* config)
				: AbstractEngine(config)
			{
				std::vector<SceneItemConfig*> sceneConfigs = config->GetSceneItems();
				if (sceneConfigs.size() <= 0) throw new EngineException("Ivalid config: scene items count.");

				SceneItemConfig* sceneConfig = sceneConfigs[0];

				m_window = new PreEngine::Windows::GLWindow<GLFWwindow>(0, m_config->GetWindowTitle(), sceneConfigs[0], m_config->GetOpenGLConfig());

				if (sceneConfig->GetSceneLayout() == SceneLayout::SINGLE) m_scene = new Scene<RootType>(0, sceneConfig);
				else m_scene = new DoubleScene<RootType>(0, sceneConfig);
			}

			template<class RootType>
			Engine<RootType>::~Engine()
			{
				SAFE_DELETE(m_scene);
				SAFE_DELETE(m_window);
			}

			template<class RootType>
			void Engine<RootType>::Init()
			{
				EventChannel::Broadcast(Core::OnEnginePreInit{});

				m_window->Init();				
				m_input->Init();
				m_audioContext->Init();
				m_scene->Init();

				EventChannel::Broadcast(Core::OnEnginePostInit{});
			}

			template<class RootType>
			void Engine<RootType>::MainLoop()
			{
				EventChannel::Broadcast(Core::OnEngineMainLoopStart{});

				m_clock->Reset();

				float deltaTime = 0.0f;
				while (!m_window->ShouldClose())
				{
					GLUtils::CheckForOpenGLError(__FILE__, __LINE__);

					m_clock->UpdateClock();
					deltaTime += m_clock->GetDelta();
					if (deltaTime >= FIXED_FRAME_PERIOD || m_unlimitedLoop)
					{
						m_input->Update(deltaTime);

						m_scene->Update(deltaTime);
						m_scene->Render();

						m_window->SwapBuffers();
						deltaTime = 0.0f;
					}

					glfwPollEvents();
				}

				EventChannel::Broadcast(Core::OnEngineMainLoopFinish{});
			}

			template<class RootType>
			void Engine<RootType>::ShutDown()
			{
				EventChannel::Broadcast(Core::OnEnginePreShutDown{});
				
				m_scene->ShutDown();
				m_audioContext->ShutDown();
				m_input->ShutDown();
				m_window->ShutDown();

				EventChannel::Broadcast(Core::OnEnginePostShutDown{});
			}

			template<class RootType>
			PreEngine::Windows::IWindow<GLFWwindow>* Engine<RootType>::GetWindow() const
			{
				return m_window;
			}

			template<class RootType>
			IScene<RootType>* Engine<RootType>::GetScene() const
			{
				return m_scene;
			}
		}
	}
}

#endif