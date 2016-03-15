/* 
 * File:   INetworObservable.h
 * Author: lubos
 *
 * Created on July 1, 2015, 1:15 PM
 */

#ifndef INETWORK_LISTENER_H
#define	INETWORK_LISTENER_H

#include "../Core/Common.h"
#include "../Utils/Serialization/Json/JsonSerializer.h"

namespace PreEngine
{
	namespace Network
	{
		using namespace PreEngine::Utils::Serialization::JSON;

		class INetworkObservable
		{
		public:
			virtual void OnConnect() = 0;

			virtual void OnMessageReceived(Json::Value& jsonRoot) = 0;

			virtual void OnDisconnect() = 0;

		public:
			virtual ~INetworkObservable() {}
		};
	}
}

#endif	/* INETWORKOBSERVABLECLIENT_H */

