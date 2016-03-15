#ifndef SCENE_ITEM_CONFIG_H
#define SCENE_ITEM_CONFIG_H

#include "../../Common.h"
#include "../../../Render/SceneLayout.h"
#include "../../Config/AbstractConfig.h"
#include "ViewFrustumConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				using namespace PreEngine::Core::Config;
				using namespace PreEngine::Render;

				class SceneItemConfig : public AbstractConfig
				{
				protected:
					SceneLayout m_sceneLayout;

					bool m_fullSceen;

					unsigned int m_width;

					unsigned int m_height;

					int m_offsetLeft;

					int m_offsetTop;

					unsigned int m_displayIndex;

					ViewFrustumConfig* m_viewFrustumConfig;

				public:
					SceneItemConfig(Json::Value root);

					virtual ~SceneItemConfig();

				public:
					void Init();

				public:
					SceneLayout GetSceneLayout() const;

					void SetSceneLayout(SceneLayout layout);

					bool IsFullScreen() const;

					void SetFullScree(bool isFullScreen);

					unsigned int GetHeight() const;

					void SetHeight(unsigned int height);

					unsigned int GetWidth() const;

					void SetWidth(unsigned int width);

					int GetOffsetLeft() const;

					void SetOffsetLeft(int offsetLeft);

					int GetOffsetTop() const;

					void SetOffsetTop(int offsetTop);			

					unsigned int GetDisplayIndex() const;

					void SetDisplayIndex(unsigned int index);

					ViewFrustumConfig* GetViewFrustumConfig() const;

					void SetViewFrustumConfig(ViewFrustumConfig* config);
				};
			}
		}
	}
}

#endif