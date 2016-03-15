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

					bool m_unlimitedLoop;

					std::vector<SceneItemConfig*> m_sceneItems;

					OpenGLConfig* m_glConfig;

				public:
					EngineConfig(std::string filePath);

					virtual ~EngineConfig();

				protected:
					void Init();

				public:
					std::string GetWindowTitle() const;

					void SetWindowTitle(std::string title);

					bool IsUnlimitedLoop() const;

					void SetUnlimitedLoop(bool unlimited);

					std::vector<SceneItemConfig*> GetSceneItems() const;

					void SetSceneItems(std::vector<SceneItemConfig*> sceneItems);

					OpenGLConfig* GetOpenGLConfig() const;

					void SetOpenGLConfig(OpenGLConfig* config);
				};
			}
		}
	}
}

#endif