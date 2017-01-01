#include "AbstractConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Config
		{
			AbstractConfig::AbstractConfig()
			{
			}

			AbstractConfig::AbstractConfig(const std::string& filePath)
				: m_filePath(filePath)
			{
				m_root = GetJsonContent(filePath);
			}

			AbstractConfig::AbstractConfig(Json::Value root)
			{
				m_root = root;
			}

			AbstractConfig::~AbstractConfig()
			{
			}

			AbstractConfig::AbstractConfig(const AbstractConfig& other)
				: m_root(other.m_root), m_filePath(other.m_filePath)
			{
			}

			AbstractConfig& AbstractConfig::operator=(const AbstractConfig& other)
			{
				if (&other != this)
				{
					m_root = other.m_root;
					m_filePath = other.m_filePath;
				}
				return *this;
			}

			Json::Value AbstractConfig::GetJsonContent(const std::string& filePath) const
			{
				Json::Value root;
				Json::Reader reader;

				FileReader fileReader;
				if (!fileReader.Open(filePath))
				{
					throw ConfigException("Could not open config file: " + filePath);
				}

				std::string fileContent = fileReader.ReadAllLines();
				bool parsingSuccessful = reader.parse(fileContent, root);
				if (!parsingSuccessful)
				{
					throw ConfigException("Failed to parse configuration" + reader.getFormattedErrorMessages());
				}
				return root;
			}

			void AbstractConfig::WriteJsonContent(const std::string& filePath, const Json::Value& value) const
			{
				FileWriter fileWriter;
				if (!fileWriter.Open(filePath))
				{
					throw ConfigException("Could not open config file: " + filePath);
				}

				Json::StreamWriterBuilder builder;
				builder["commentStyle"] = "None";
				builder["indentation"] = "   ";
				std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
				std::stringstream ss;
				jsonWriter->write(value, &ss);			
				fileWriter.WriteLine(ss.str());
			}

			Json::Value AbstractConfig::GetRoot() const
			{
				return m_root;
			}
		}
	}
}