/* 
 * File:   NetworkClient.h
 * Author: lubos
 *
 * Created on July 1, 2015, 9:58 AM
 */

#ifndef NETWORKCLIENT_H
#define	NETWORKCLIENT_H

#include "Commands/NetworkCommandFactory.h"
#include "TCP/TCPStreamClient.h"

#include "INetworkClient.h"

#include "../Utils/Time/Timers/Timer.h"
#include "../Utils/Time/Timers/ITimerObservable.h"

namespace PreEngine
{
	namespace Network
	{
		using namespace PreEngine::Network::TCP;
		using namespace PreEngine::Network::Commands;
		using namespace PreEngine::Utils::Time::Timers;
		using namespace PreEngine::Utils::Log;

		template<class ProtocolClientType> 
		class NetworkClient : public INetworkClient, public INetworkObservable, public ITimerObservable
		{
		protected:
			std::string m_host;

			int m_port;

			ProtocolClientType* m_streamClient;

			INetworkCommandFactory* m_networkCommandFactory;

			ITimer* m_connectionCheckTimer;

		public:
			NetworkClient(std::string host, int port);

			virtual ~NetworkClient();

		public:
			bool Connect();

			void Disconnect();

		public:
			void OnTimeout();

			void OnTimerFinished();
		};


		template<class ProtocolClientType>
		NetworkClient<ProtocolClientType>::NetworkClient(std::string host, int port)
			: m_host(host), m_port(port)
		{
			m_networkCommandFactory = new NetworkCommandFactory();
			m_streamClient = new ProtocolClientType();
			m_streamClient->RegisterListener(this);
			m_connectionCheckTimer = new Timer(5000, false);
			m_connectionCheckTimer->RegisterListener(this);
		}

		template<class ProtocolClientType>
		NetworkClient<ProtocolClientType>::~NetworkClient()
		{
			SAFE_DELETE(m_connectionCheckTimer);
			SAFE_DELETE(m_streamClient);
			SAFE_DELETE(m_networkCommandFactory);
		}

		template<class ProtocolClientType>
		bool NetworkClient<ProtocolClientType>::Connect()
		{
			bool retVal = m_streamClient->Connect(m_host, m_port);
			m_streamClient->RunThread();
			m_connectionCheckTimer->Start();
			return retVal;
		}

		template<class ProtocolClientType>
		void NetworkClient<ProtocolClientType>::Disconnect()
		{
			m_streamClient->Disconnect();
			m_streamClient->Join();
			m_connectionCheckTimer->Stop();
		}

		template<class ProtocolClientType>
		void NetworkClient<ProtocolClientType>::OnTimeout()
		{
			if (!m_streamClient->IsConnected())
			{
				m_streamClient->Disconnect();
				m_streamClient->Connect(m_host, m_port);
			}
		}

		template<class ProtocolClientType>
		void NetworkClient<ProtocolClientType>::OnTimerFinished()
		{
		}
	}
}

#endif	/* NETWORKCLIENT_H */

