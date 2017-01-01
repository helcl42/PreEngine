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

				SceneItemConfig::SceneItemConfig(const SceneItemConfig& other)
					: AbstractConfig(other), m_isInFullScreen(other.m_isInFullScreen), m_isDecorated(other.m_isDecorated), m_width(other.m_width), m_height(other.m_height), m_offsetLeft(other.m_offsetLeft), m_offsetTop(other.m_offsetTop), m_displayIndex(other.m_displayIndex), m_sceneEye(other.m_sceneEye)
				{
					SAFE_DELETE(m_viewFrustumConfig);
					m_viewFrustumConfig = other.m_viewFrustumConfig != NULL ? new ViewFrustumConfig(*other.m_viewFrustumConfig) : NULL;
				}

				SceneItemConfig& SceneItemConfig::operator=(const SceneItemConfig& other)
				{
					if (&other != this)
					{
						AbstractConfig::operator=(other);
						m_isInFullScreen = other.m_isInFullScreen;
						m_isDecorated = other.m_isDecorated; 
						m_width = other.m_width; 
						m_height = other.m_height; 
						m_offsetLeft = other.m_offsetLeft;
						m_offsetTop = other.m_offsetTop;
						m_displayIndex = other.m_displayIndex;
						m_sceneEye = other.m_sceneEye;
						SAFE_DELETE(m_viewFrustumConfig);
						m_viewFrustumConfig = other.m_viewFrustumConfig != NULL ? new ViewFrustumConfig(*other.m_viewFrustumConfig) : NULL;
					}
					return *this;
				}

				void SceneItemConfig::Init()
				{
					m_isInFullScreen = m_root.isMember("FullScreen") ? m_root["FullScreen"].asBool() : false;
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

				Json::Value SceneItemConfig::GetValue() const
				{
					Json::Value newRoot;
					newRoot["FullScreen"] = m_isInFullScreen;
					newRoot["IsDecorated"] = m_isDecorated;
					newRoot["Width"] = m_width;
					newRoot["Height"] = m_height;
					newRoot["Top"] = m_offsetTop;
					newRoot["Left"] = m_offsetLeft;
					newRoot["DisplayIndex"] = m_displayIndex;
					if (m_viewFrustumConfig != NULL) newRoot["ViewFrustum"] = m_viewFrustumConfig->GetValue();

					switch (m_sceneEye)
					{
					case SceneEye::LEFT_EYE:
						newRoot["SceneEye"] = "LEFT_EYE";
						break;
					case SceneEye::RIGHT_EYE:
						newRoot["SceneEye"] = "RIGHT_EYE";
						break;
					case SceneEye::LEFT_RIGHT_EYE:
						newRoot["SceneEye"] = "LEFT_RIGHT_EYE";
						break;
					case SceneEye::TOP_BOTTOM_EYE:
						newRoot["SceneEye"] = "TOP_BOTTOM_EYE";
						break;
					default:
						newRoot["SceneEye"] = "CENTER_EYE";
						break;
					}
					return newRoot;
				}

				bool SceneItemConfig::IsFullScreen() const
				{
					return m_isInFullScreen;
				}

				void SceneItemConfig::SetFullScreen(bool isFullScreen)
				{
					m_isInFullScreen = isFullScreen;
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
