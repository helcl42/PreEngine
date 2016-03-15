/* 
 * File:   INetworkClient.h
 * Author: lubos
 *
 * Created on July 1, 2015, 11:08 AM
 */

#ifndef INETWORKCLIENT_H
#define	INETWORKCLIENT_H

#include "../Core/Common.h"
#include "../Utils/Serialization/Json/JsonSerializer.h"

namespace PreEngine
{
	namespace Network
	{
		using namespace PreEngine::Utils::Serialization::JSON;

		class INetworkClient
		{
		public:
			virtual bool Connect() = 0;

			virtual void Disconnect() = 0;

			virtual bool Send(IJsonSerializable* messageObject) = 0;

		public:
			virtual ~INetworkClient() {} 
		};
	}
}

#endif	/* INETWORKCLIENT_H */

