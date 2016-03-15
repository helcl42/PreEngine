/* 
 * File:   IJsonSerializable.h
 * Author: lubos
 *
 * Created on July 1, 2015, 11:11 AM
 */

#ifndef IJSONSERIALIZABLE_H
#define	IJSONSERIALIZABLE_H

#include <json/json.h>

#include "../../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Serialization
		{
			namespace JSON
			{
				class IJsonSerializable
				{
				public:
					virtual ~IJsonSerializable(void)
					{
					}

				public:
					virtual void Serialize(Json::Value& root) = 0;

					virtual void Deserialize(Json::Value& root) = 0;
				};
			}
		}
	}
}

#endif	/* IJSONSERIALIZABLE_H */

