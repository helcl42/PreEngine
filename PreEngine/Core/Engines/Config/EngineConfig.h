#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

#include "../../Common.h"
#include "../../Config/AbstractConfig.h"
#include "SceneItemConfig.h"
#include "OpenGLConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{			
				class EngineConfig : public AbstractConfig
				{
				protected:
					std::string m_windowTitle;

					bool m_vSync;

					std::vector<SceneItemConfig*> m_sceneItems;

					OpenGLConfig* m_glConfig;

				public:
					EngineConfig(std::string filePath);

					virtual ~EngineConfig();

				public:
					EngineConfig(const EngineConfig& other);

					EngineConfig& operator=(const EngineConfig& other);

				protected:
					void Init();

				public:
					Json::Value GetValue() const;

					virtual void Sync() const;

				public:
					std::string GetWindowTitle() const;

					void SetWindowTitle(std::string title);

					bool IsVSyncEnabled() const;

					void SetVSyncEnabled(bool enabled);

					std::vector<SceneItemConfig*> GetSceneItems() const;

					SceneItemConfig* GetSceneItem(unsigned int index) const;

					void SetSceneItems(std::vector<SceneItemConfig*> sceneItems);

					OpenGLConfig* GetOpenGLConfig() const;

					void SetOpenGLConfig(OpenGLConfig* config);
				};
			}
		}
	}
}

#endif