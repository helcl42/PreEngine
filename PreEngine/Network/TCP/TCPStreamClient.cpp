#include "TCPStreamClient.h"
#include "../NetworkClient.h"

namespace PreEngine
{
	namespace Network
	{
		namespace TCP
		{
			TCPStreamClient::TCPStreamClient()
			{
			}

			TCPStreamClient::~TCPStreamClient()
			{
				SAFE_DELETE(m_clientSocket);
			};

			bool TCPStreamClient::Connect(std::string host, int port)
			{
				Logger::GetInstance().Debug() << "Trying connect to: " << host << ":" << port;

				m_clientSocket = new TCPClientSocket(host, port);
				if (!m_clientSocket->Open())
				{
					m_isConnected = false;
					Logger::GetInstance().Error() << "Socket was not opened.";
					return false;
				}

				m_isConnected = true;

				const std::vector<INetworkObservable*>& observables = m_observer.GetObservables();
				for (std::vector<INetworkObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
				{
					(*ci)->OnConnect();
				}
				return true;
			}

			bool TCPStreamClient::Disconnect()
			{
				m_clientSocket->Close();
				m_isConnected = false;
				const std::vector<INetworkObservable*>& observables = m_observer.GetObservables();
				for (std::vector<INetworkObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
				{
					(*ci)->OnDisconnect();
				}
				return true;
			}

			void TCPStreamClient::OnThreadStarted()
			{
				Logger::GetInstance().Debug() << "TCPStreamClient Receive thread started.";
			}

			void TCPStreamClient::ThreadProcedure()
			{
				while (!m_isFinished)
				{
					if (Receive())
					{
						Json::Value jsonRoot;
						Json::Reader jsonReader;
						Logger::GetInstance().Debug() << "Received Message: '" << m_message << "'";
						if (jsonReader.parse(m_message, jsonRoot))
						{
							const std::vector<INetworkObservable*>& observables = m_observer.GetObservables();
							for (std::vector<INetworkObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
							{
								(*ci)->OnMessageReceived(jsonRoot);
							}
						}
						else
						{
							Logger::GetInstance().Error() << "FAILED to parse Received message: " << m_message;
						}
						m_message = "";
					}

					std::this_thread::sleep_for(std::chrono::microseconds(50000));
				}
			}

			void TCPStreamClient::OnThreadFinished()
			{
				Logger::GetInstance().Debug() << "TCPStreamClient Receive thread finished.";
			}

			bool TCPStreamClient::Send(std::string message)
			{
				int sendDataLength = 0;
				int shift = 0;

				message += MESSAGE_DELIMITER;

				const char* data = message.c_str();
				int dataLength = (int)message.length();

				do
				{
					sendDataLength = send(m_clientSocket->GetSocket(), (data + shift), dataLength, 0);
					if (sendDataLength < 0)
					{
						Logger::GetInstance().Error() << "Content of send message has invalid size.";
						return false;
					}
					dataLength -= sendDataLength;
					shift += sendDataLength;
				} 
				while (dataLength > 0);

				return true;
			}

			bool TCPStreamClient::Receive() // TODO optimize
			{
				char tempByte;
				int partSize = 0;
				int dataLength = 0;

				while (true)
				{
					partSize = recv(m_clientSocket->GetSocket(), static_cast<char*> (&tempByte), 1, 0);
					if (partSize < 0) return false;
					if (tempByte == MESSAGE_DELIMITER) return true;

					dataLength += partSize;
					m_message += tempByte;
				}

				return false;
			}

			bool TCPStreamClient::IsConnected() const
			{
				return m_isConnected && m_clientSocket->IsOpen();
			}

			bool TCPStreamClient::RegisterListener(INetworkObservable* observable)
			{
				return m_observer.RegisterListener(observable);
			}

			bool TCPStreamClient::UnregisterListener(INetworkObservable* observable)
			{
				return m_observer.UnregisterListener(observable);
			}
		}
	}
}
