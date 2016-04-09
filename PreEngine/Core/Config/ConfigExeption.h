#ifndef CONFIG_EXCEPTION_H
#define CONFIG_EXCEPTION_H

#include "../Common.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Config
		{
			using namespace Utils::Log;

			class ConfigException : public std::runtime_error
			{
			public:
				ConfigException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~ConfigException()
				{
				}
			};
		}
	}
}

#endif