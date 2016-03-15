/* 
 * File:   StreamClient.h
 * Author: lubos
 *
 * Created on June 30, 2015, 3:47 PM
 */

#ifndef STREAMCLIENT_H
#define	STREAMCLIENT_H

#include <json/json.h>

#include "../../Core/Common.h"
#include "../../Core/Threading/Thread.h"
#include "../../Core/Observer.h"

#include "TCPClientSocket.h"
#include "../INetworkObservable.h"

namespace PreEngine
{
	namespace Network
	{
		namespace TCP
		{
			using namespace PreEngine::Utils::Log;
			using namespace PreEngine::Core::Threading;
			using namespace PreEngine::Network;
			using namespace PreEngine::Core;

			class TCPStreamClient : public Thread
			{
			protected:
				bool m_isConnected = false;

				ITCPClientSocket* m_clientSocket = NULL;

				const char MESSAGE_DELIMITER = '\n';

				std::string m_message;

				Observer<INetworkObservable> m_observer;

			public:
				TCPStreamClient();

				virtual ~TCPStreamClient();

			public:
				void OnThreadStarted();

				void ThreadProcedure();

				void OnThreadFinished();

			public:
				bool Connect(std::string host, int port);

				bool Disconnect();

				bool Send(std::string message);

				bool Receive();

				bool RegisterListener(INetworkObservable* client);

				bool UnregisterListener(INetworkObservable* client);

			public:
				bool IsConnected() const;
			};
		}
	}
}

#endif	/* STREAMCLIENT_H */

