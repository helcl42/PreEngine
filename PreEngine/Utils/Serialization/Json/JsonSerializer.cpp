#include "JsonSerializer.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Serialization
		{
			namespace JSON
			{
				bool JsonSerializer::Serialize(IJsonSerializable* obj, std::string& output)
				{
					if (obj == NULL) return false;

					Json::Value serializeRoot;
					obj->Serialize(serializeRoot);

					Json::FastWriter writer;
					output = writer.write(serializeRoot);

					return true;
				}

				bool JsonSerializer::Deserialize(IJsonSerializable* obj, std::string& input)
				{
					if (obj == NULL) return false;

					Json::Value deserializeRoot;
					Json::Reader reader;

					if (!reader.parse(input, deserializeRoot)) return false;

					obj->Deserialize(deserializeRoot);

					return true;
				}
			}
		}
	}
}