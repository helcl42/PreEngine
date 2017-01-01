#ifndef SCENE_ITEM_CONFIG_H
#define SCENE_ITEM_CONFIG_H

#include "../../Common.h"
#include "../../../Render/SceneEye.h"
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
					bool m_isInFullScreen;

					bool m_isDecorated;

					unsigned int m_width;

					unsigned int m_height;

					int m_offsetLeft;

					int m_offsetTop;

					unsigned int m_displayIndex;

					SceneEye m_sceneEye;

					ViewFrustumConfig* m_viewFrustumConfig;

				public:
					SceneItemConfig(Json::Value root);

					virtual ~SceneItemConfig();

				public:
					SceneItemConfig(const SceneItemConfig& other);

					SceneItemConfig& operator=(const SceneItemConfig& other);

				public:
					void Init();

					virtual Json::Value GetValue() const;

				public:
					bool IsFullScreen() const;

					void SetFullScreen(bool isFullScreen);

					bool IsDecorated() const;

					void SetDecorated(bool has);

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

					SceneEye GetSceneEye() const;

					void SetSceneEye(SceneEye eye);
				};
			}
		}
	}
}

#endif