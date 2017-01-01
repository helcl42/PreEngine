#ifndef OPENGL_CONFIG_H
#define OPENGL_CONFIG_H

#include "../../Config/AbstractConfig.h" 

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				using namespace PreEngine::Core::Config;

				class OpenGLConfig : public AbstractConfig
				{
				protected:
					unsigned int m_majorVersion = 4;

					unsigned int m_minorVersion = 3;

					unsigned int m_antialiazingLevel = 4;

				public:
					OpenGLConfig();

					OpenGLConfig(Json::Value root);

					virtual ~OpenGLConfig();

				public:
					OpenGLConfig(const OpenGLConfig& other);

					OpenGLConfig& operator=(const OpenGLConfig& other);

				public:
					void Init();

					Json::Value GetValue() const;

				public:
					unsigned int GetMajorVersion() const;

					void SetMajorVersion(unsigned int version);

					unsigned int GetMinorVersion() const;

					void SetMinorVersion(unsigned int version);

					unsigned int GetAntializingLevel() const;

					void SetAntialiazingLevel(unsigned int level);
				};
			}
		}
	}
}
#endif