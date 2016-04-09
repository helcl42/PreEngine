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
					std::string layoutString = m_root["SceneLayout"].asString();
					if (layoutString == "OVER_UNDER") m_sceneLayout = SceneLayout::OVER_UNDER;
					else if (layoutString == "SIDE_BY_SIDE") m_sceneLayout = SceneLayout::SIDE_BY_SIDE;
					else m_sceneLayout = SceneLayout::SINGLE;

					m_isInFullSceen = m_root["FullScreen"].asBool();
					m_isDecorated = m_root["IsDecorated"].asBool();
					m_width = m_root["Width"].asUInt();
					m_height = m_root["Height"].asUInt();

					m_offsetTop = m_root.isMember("Top") ? m_root["Top"].asInt() : 60;
					m_offsetLeft = m_root.isMember("Left") ? m_root["Left"].asInt() : 30;

					m_displayIndex = m_root["DisplayIndex"].asUInt();

					if (m_root.isMember("ViewFrustum")) m_viewFrustumConfig = new ViewFrustumConfig(m_root["ViewFrustum"]);
				}

				SceneLayout SceneItemConfig::GetSceneLayout() const
				{
					return m_sceneLayout;
				}

				void SceneItemConfig::SetSceneLayout(SceneLayout layout)
				{
					m_sceneLayout = layout;
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
			}
		}
	}
}
