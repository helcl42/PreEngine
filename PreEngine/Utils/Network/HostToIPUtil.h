/*
 * File:   HostToIPUtil.h
 * Author: lubos
 *
 * Created on July 3, 2015, 10:20 AM
 */

#ifndef HOST_TO_IP_UTIL_H
#define HOST_TO_IP_UTIL_H

#include "../../Core/Common.h"

#ifdef _WIN32
#include <WS2tcpip.h>
#else
// TODO
#endif

namespace PreEngine
{
	namespace Utils
	{
		namespace Network
		{
			using namespace PreEngine::Utils::Log;

			class HostToIPUtil
			{
			public:
				static addrinfo* GetAddressInfo(const std::string& host);

				static void PrintAddressInfo(const std::string& host);
			};
		}
	}
}

#endif