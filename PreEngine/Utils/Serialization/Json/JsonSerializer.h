/* 
 * File:   JsonSerializer.h
 * Author: lubos
 *
 * Created on July 1, 2015, 11:12 AM
 */

#ifndef JSONSERIALIZER_H
#define	JSONSERIALIZER_H

#include "../../../Core/Common.h"
#include "IJsonSerializable.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Serialization
		{
			namespace JSON
			{
				class JsonSerializer
				{
				public:
					static bool Serialize(IJsonSerializable* obj, std::string& output);

					static bool Deserialize(IJsonSerializable* obj, std::string& input);

				private:
					JsonSerializer() {}
				};
			}
		}
	}
}

#endif	/* JSONSERIALIZER_H */

