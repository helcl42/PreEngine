#include "OpenGLConfig.h"


namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				OpenGLConfig::OpenGLConfig()
					: AbstractConfig()
				{
				}

				OpenGLConfig::OpenGLConfig(Json::Value root)
					: AbstractConfig(root)
				{
					Init();
				}

				OpenGLConfig::~OpenGLConfig()
				{
				}

				void OpenGLConfig::Init()
				{
					if (m_root.isMember("MajorVersion"))
					{
						m_majorVersion = m_root["MajorVersion"].asUInt();
					}

					if (m_root.isMember("MinorVersion"))
					{
						m_minorVersion = m_root["MinorVersion"].asUInt();
					}

					if (m_root.isMember("AntialiazingLevel"))
					{
						m_antialiazingLevel = m_root["AntialiazingLevel"].asUInt();
					}
				}

				unsigned int OpenGLConfig::GetMajorVersion() const
				{
					return m_majorVersion;
				}

				void OpenGLConfig::SetMajorVersion(unsigned int version)
				{
					m_majorVersion = version;
				}

				unsigned int OpenGLConfig::GetMinorVersion() const
				{
					return m_minorVersion;
				}

				void OpenGLConfig::SetMinorVersion(unsigned int version)
				{
					m_minorVersion = version;
				}

				unsigned int OpenGLConfig::GetAntializingLevel() const
				{
					return m_antialiazingLevel;
				}

				void OpenGLConfig::SetAntialiazingLevel(unsigned int level)
				{
					m_antialiazingLevel = level;
				}
			}
		}
	}
}