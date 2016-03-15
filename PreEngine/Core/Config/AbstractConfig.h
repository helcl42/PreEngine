#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <json/json.h>

#include "../Common.h"
#include "ConfigExeption.h"

#include "../../Utils/IO/FileReader.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Config
		{
			using namespace Utils::IO;

			class AbstractConfig
			{
			protected:
				Json::Value m_root;

			public:
				AbstractConfig();

				AbstractConfig(std::string filePath);

				AbstractConfig(Json::Value root);

				virtual ~AbstractConfig();

			protected:
				Json::Value GetJsonContent(std::string filePath);

			protected:
				virtual void Init() = 0;

			public:
				Json::Value GetRoot() const;
			};
		}
	}
}

#endif