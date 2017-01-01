#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <json/json.h>

#include "../Common.h"
#include "ConfigExeption.h"

#include "../../Utils/IO/FileReader.h"
#include "../../Utils/IO/FileWriter.h"

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

				std::string m_filePath;

			public:
				AbstractConfig();

				AbstractConfig(const std::string& filePath);

				AbstractConfig(Json::Value root);

				virtual ~AbstractConfig();

			public:
				AbstractConfig(const AbstractConfig& other);

				AbstractConfig& operator=(const AbstractConfig& other);

			protected:
				Json::Value GetJsonContent(const std::string& filePath) const;

				void WriteJsonContent(const std::string& filePath, const Json::Value& value) const;

			protected:
				virtual void Init() = 0;

			public:
				Json::Value GetRoot() const;

				virtual Json::Value GetValue() const = 0;
			};
		}
	}
}

#endif