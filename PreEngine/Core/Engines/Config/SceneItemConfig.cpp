#include "SceneItemConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				SceneItemConfig::SceneItemConfig(Json::Value root)
					: AbstractConfig(root)
				{
					Init();
				}

				SceneItemConfig::~SceneItemConfig()
				{
					SAFE_DELETE(m_viewFrustumConfig);
				}

				void SceneItemConfig::Init()
				{
					m_isInFullSceen = m_root.isMember("FullScreen") ? m_root["FullScreen"].asBool() : false;
					m_isDecorated = m_root.isMember("IsDecorated") ? m_root["IsDecorated"].asBool() : true;
					m_width = m_root["Width"].asUInt();
					m_height = m_root["Height"].asUInt();

					m_offsetTop = m_root.isMember("Top") ? m_root["Top"].asInt() : 60;
					m_offsetLeft = m_root.isMember("Left") ? m_root["Left"].asInt() : 30;

					m_displayIndex = m_root["DisplayIndex"].asInt();

					if (m_root.isMember("ViewFrustum")) m_viewFrustumConfig = new ViewFrustumConfig(m_root["ViewFrustum"]);

					std::string sceneEye = m_root["SceneEye"].asString();
					if (sceneEye == "LEFT_EYE") m_sceneEye = SceneEye::LEFT_EYE;
					else if (sceneEye == "RIGHT_EYE") m_sceneEye = SceneEye::RIGHT_EYE;
					else if (sceneEye == "LEFT_RIGHT_EYE") m_sceneEye = SceneEye::LEFT_RIGHT_EYE;
					else if (sceneEye == "TOP_BOTTOM_EYE") m_sceneEye = SceneEye::TOP_BOTTOM_EYE;
					else m_sceneEye = SceneEye::CENTER_EYE;
				}

				bool SceneItemConfig::IsFullScreen() const
				{
					return m_isInFullSceen;
				}

				void SceneItemConfig::SetFullScreen(bool isFullScreen)
				{
					m_isInFullSceen = isFullScreen;
				}

				bool SceneItemConfig::IsDecorated() const
				{
					return m_isDecorated;
				}

				void SceneItemConfig::SetDecorated(bool has)
				{
					m_isDecorated = has;
				}

				unsigned int SceneItemConfig::GetHeight() const
				{
					return m_height;
				}

				void SceneItemConfig::SetHeight(unsigned int height)
				{
					m_height = height;
				}

				unsigned int SceneItemConfig::GetWidth() const
				{
					return m_width;
				}

				void SceneItemConfig::SetWidth(unsigned int width)
				{
					m_width = width;
				}

				int SceneItemConfig::GetOffsetLeft() const
				{
					return m_offsetLeft;
				}

				void SceneItemConfig::SetOffsetLeft(int offsetLeft)
				{
					m_offsetLeft = offsetLeft;
				}

				int SceneItemConfig::GetOffsetTop() const
				{
					return m_offsetTop;
				}

				void SceneItemConfig::SetOffsetTop(int offsetTop)
				{
					m_offsetTop = offsetTop;
				}

				unsigned int SceneItemConfig::GetDisplayIndex() const
				{
					return m_displayIndex;
				}

				void SceneItemConfig::SetDisplayIndex(unsigned int index)
				{
					m_displayIndex = index;
				}

				ViewFrustumConfig* SceneItemConfig::GetViewFrustumConfig() const
				{
					return m_viewFrustumConfig;
				}

				void SceneItemConfig::SetViewFrustumConfig(ViewFrustumConfig* config)
				{
					m_viewFrustumConfig = config;
				}

				SceneEye SceneItemConfig::GetSceneEye() const
				{
					return m_sceneEye;
				}

				void SceneItemConfig::SetSceneEye(SceneEye eye)
				{
					m_sceneEye = eye;
				}
			}
		}
	}
}
