/* 
 * File:   TCPClientSocket.h
 * Author: lubos
 *
 * Created on June 30, 2015, 3:44 PM
 */

#ifndef TCPCLIENTSOCKET_H
#define	TCPCLIENTSOCKET_H

#ifdef _WIN32
#include <winsock2.h>
//#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
static inline int poll(struct pollfd* pfd, int nfds, int timeout) { return WSAPoll(pfd, nfds, timeout); }
#else
typedef int SOCKET 
#endif

#include "../../Core/Common.h"
#include "../../Utils/Network/HostToIPUtil.h"

#include "ITCPClientSocket.h"

namespace PreEngine
{
	namespace Network
	{
		namespace TCP
		{
			using namespace PreEngine::Utils::Log;
			using namespace PreEngine::Utils::Network;

			class TCPClientSocket : public ITCPClientSocket
			{
			protected:
				SOCKET m_socket;

				struct pollfd m_pollFileDescriptor;

				std::string m_hostname;

				int m_port;

			public:
				TCPClientSocket(std::string hostname, int port);

				virtual ~TCPClientSocket();

			public:
				bool Open();

				bool IsOpen();

				SOCKET GetSocket() const;

				void Close();
			};
		}
	}
}

#endif	/* TCPCLIENTSOCKET_H */

