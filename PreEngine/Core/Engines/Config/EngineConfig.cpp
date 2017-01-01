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

				EngineConfig::EngineConfig(const EngineConfig& other)
					: AbstractConfig(other), m_windowTitle(other.m_windowTitle), m_vSync(other.m_vSync)
				{
					for (auto& item : m_sceneItems)
					{
						SAFE_DELETE(item);
					}
					m_sceneItems.clear();

					for (const auto& item : other.m_sceneItems)
					{
						m_sceneItems.push_back(new SceneItemConfig(*item));
					}

					SAFE_DELETE(m_glConfig);
					m_glConfig = other.m_glConfig != NULL ? new OpenGLConfig(*other.m_glConfig) : NULL;
				}

				EngineConfig& EngineConfig::operator=(const EngineConfig& other)
				{
					if (&other != this)
					{
						AbstractConfig::operator=(other);
						m_windowTitle = other.m_windowTitle;
						m_vSync = other.m_vSync;
						
						for (auto& item : m_sceneItems)
						{
							SAFE_DELETE(item);
						}
						m_sceneItems.clear();

						for (const auto& item : other.m_sceneItems)
						{
							m_sceneItems.push_back(new SceneItemConfig(*item));
						}

						SAFE_DELETE(m_glConfig);
						m_glConfig = other.m_glConfig != NULL ? new OpenGLConfig(*other.m_glConfig) : NULL;
					}
					return *this;
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

				Json::Value EngineConfig::GetValue() const
				{
					Json::Value newRoot;
					newRoot["WindowTitle"] = m_windowTitle;
					Json::Value scenes(Json::arrayValue);					
					for (auto scene : m_sceneItems)
					{
						scenes.append(scene->GetValue());
					}
					newRoot["Scenes"] = scenes;
					newRoot["VSync"] = m_vSync;
					newRoot["OpenGL"] = m_glConfig->GetValue();
					return newRoot;
				}

				void EngineConfig::Sync() const
				{
					Json::Value val = GetValue();
					WriteJsonContent(m_filePath, val);
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