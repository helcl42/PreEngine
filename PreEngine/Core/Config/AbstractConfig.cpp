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

			AbstractConfig::AbstractConfig(std::string filePath)
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

			Json::Value AbstractConfig::GetJsonContent(std::string filePath)
			{
				Json::Value root;
				Json::Reader reader;

				FileReader m_fileReader;
				if (!m_fileReader.Open(filePath))
				{
					throw new ConfigException("Could not open config file: " + filePath);
				}

				std::string fileContent = m_fileReader.ReadAllLines();
				bool parsingSuccessful = reader.parse(fileContent, root);
				if (!parsingSuccessful)
				{
					throw new ConfigException("Failed to parse configuration" + reader.getFormatedErrorMessages());
				}
				return root;
			}

			Json::Value AbstractConfig::GetRoot() const
			{
				return m_root;
			}
		}
	}
}