#include "TCPClientSocket.h"

namespace PreEngine
{
	namespace Network
	{
		namespace TCP
		{
			TCPClientSocket::TCPClientSocket(std::string hostname, int port)
			{
				m_hostname = hostname;
				m_port = port;
			}

			TCPClientSocket::~TCPClientSocket()
			{
			}

			bool TCPClientSocket::Open()
			{
#ifdef _WIN32
				WSADATA wsaData;
				int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
				if (result != 0) 
				{
					Logger::GetInstance().Error() << " Error while Initializing winsocket context: " << result;
					Close();
					return false;
				}
#endif
				struct sockaddr_in serverAddress;
				m_socket = socket(AF_INET, SOCK_STREAM, 0);
				if (m_socket < 0)
				{
					Logger::GetInstance().Error() << " Error while creating socket.";
					Close();
					return false;
				}

				HostToIPUtil::PrintAddressInfo(m_hostname);

				addrinfo* addrInfo = HostToIPUtil::GetAddressInfo(m_hostname);
				if (addrInfo == NULL)
				{
					Logger::GetInstance().Error() << "Host '" << m_hostname << "' does not exist.";
					Close();
					return false;
				}
				
				memset((void*)&serverAddress, 0, sizeof(serverAddress));
				serverAddress.sin_family = AF_INET;
				serverAddress.sin_port = htons(m_port);

				struct sockaddr_in* addrIn = (struct sockaddr_in*)addrInfo->ai_addr;
				memcpy(&serverAddress.sin_addr.s_addr, &addrIn->sin_addr, (addrIn->sin_family == PF_INET6) ? 6 : 4);
				freeaddrinfo(addrInfo);

				if (connect(m_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
				{
					Logger::GetInstance().Error() << "Error occoured while connecting to the server.";
					Close();
					return false;
				}
				
				u_long mode = 1; // If mode != 0, non-blocking mode is enabled.
				ioctlsocket(m_socket, FIONBIO, &mode);

				m_pollFileDescriptor.fd = m_socket;
				m_pollFileDescriptor.events = POLLOUT;
				return true;
			}

			bool TCPClientSocket::IsOpen()
			{
				int n = send(m_socket, "\n", 1, 0); // hack
				if (n < 0)
				{
					Logger::GetInstance().Error() << "TCP client socket: not opened.";
					return false;
				}
				return true;

				//int pollResult = poll(&m_pollFileDescriptor, 1, 1000);
				//switch (pollResult)
				//{
				//case 0: // poll timeout
				//	Logger::GetInstance().Error() << "TCP client socket: Poll Timeout has expired!";
				//	return false;

				//case -1: // poll error
				//	Logger::GetInstance().Error() << "TCP client socket: Error on poll.";
				//	return false;

				//default:
				//	return true;
				//}
			}

			SOCKET TCPClientSocket::GetSocket() const
			{
				return m_socket;
			}

			void TCPClientSocket::Close()
			{
				//shutdown(m_socket, SD_BOTH);
				closesocket(m_socket);
#ifdef _WIN32
				WSACleanup();
#endif
			}
		}
	}
}
