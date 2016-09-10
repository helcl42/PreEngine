#include "EngineConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				EngineConfig::EngineConfig(std::string filePath)
					: AbstractConfig(filePath)
				{
					Init();
				}

				EngineConfig::~EngineConfig()
				{
					for (std::vector<SceneItemConfig*>::iterator ii = m_sceneItems.begin(); ii != m_sceneItems.end(); ++ii)
					{
						SAFE_DELETE(*ii);
					}

					SAFE_DELETE(m_glConfig);
				}

				void EngineConfig::Init()
				{
					m_windowTitle = m_root["WindowTitle"].asString();

					const Json::Value scenes = m_root["Scenes"];
					for (unsigned int index = 0; index < scenes.size(); ++index)
					{
						const Json::Value scene = scenes[index];

						SceneItemConfig* item = new SceneItemConfig(scene);
						m_sceneItems.push_back(item);
					}

					m_vSync = false;
					if (m_root.isMember("VSync"))
					{
						m_vSync = m_root["VSync"].asBool();
					}

					if (m_root.isMember("OpenGL"))
					{
						m_glConfig = new OpenGLConfig(m_root["OpenGL"]);
					}
					else
					{
						m_glConfig = new OpenGLConfig();
					}
				}

				std::string EngineConfig::GetWindowTitle() const
				{
					return m_windowTitle;
				}

				void EngineConfig::SetWindowTitle(std::string title)
				{
					m_windowTitle = title;
				}

				bool EngineConfig::IsVSyncEnabled() const
				{
					return m_vSync;
				}

				void EngineConfig::SetVSyncEnabled(bool enabled)
				{
					m_vSync = enabled;
				}
			
				std::vector<SceneItemConfig*> EngineConfig::GetSceneItems() const
				{
					return m_sceneItems;
				}

				SceneItemConfig* EngineConfig::GetSceneItem(unsigned int index) const
				{
					return m_sceneItems[index];
				}

				void EngineConfig::SetSceneItems(std::vector<SceneItemConfig*> sceneItems)
				{
					m_sceneItems = sceneItems;
				}

				OpenGLConfig* EngineConfig::GetOpenGLConfig() const
				{
					return m_glConfig;
				}

				void EngineConfig::SetOpenGLConfig(OpenGLConfig* config)
				{
					m_glConfig = config;
				}
			}
		}
	}
}