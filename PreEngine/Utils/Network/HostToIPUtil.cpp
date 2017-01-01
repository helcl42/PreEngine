#include "HostToIPUtil.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Network
		{
			addrinfo* HostToIPUtil::GetAddressInfo(const std::string& host)
			{
				struct addrinfo hints, *result = NULL;
				
				memset(&hints, 0, sizeof(hints));
				//hints.ai_family = AF_UNSPEC;
				//hints.ai_socktype = SOCK_STREAM;
				//hints.ai_protocol = IPPROTO_TCP;

				if (getaddrinfo(host.c_str(), NULL, &hints, &result) != 0) return NULL;
				return result;
			}

			addrinfo* HostToIPUtil::GetAddressInfo(const std::string& host, const int port)
			{
				struct addrinfo hints, *result = NULL;

				memset(&hints, 0, sizeof(hints));
				//hints.ai_family = AF_UNSPEC;
				//hints.ai_socktype = SOCK_STREAM;
				//hints.ai_protocol = IPPROTO_TCP;

				if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result) != 0) return NULL;
				return result;
			}

			addrinfo* HostToIPUtil::GetAddressInfo(const int port)
			{
				struct addrinfo hints, *result = NULL;

				memset(&hints, 0, sizeof(hints));
				//hints.ai_family = AF_UNSPEC;
				//hints.ai_socktype = SOCK_STREAM;
				//hints.ai_protocol = IPPROTO_TCP;

				if (getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &result) != 0) return NULL;
				return result;
			}

			void HostToIPUtil::PrintAddressInfo(const std::string& host)
			{
				char addrstr[100];
				void *ptr = NULL;

				std::stringstream ss;
				ss << "Host: " << host << std::endl;

				addrinfo* res = HostToIPUtil::GetAddressInfo(host);
				addrinfo* origin = res;

				while (res)
				{
					inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

					switch (res->ai_family)
					{
					case AF_INET:
						ptr = &((struct sockaddr_in*)res->ai_addr)->sin_addr;
						break;
					case AF_INET6:
						ptr = &((struct sockaddr_in6*)res->ai_addr)->sin6_addr;
						break;
					}
					inet_ntop(res->ai_family, ptr, addrstr, 100);

					ss << "IPv" << (res->ai_family == PF_INET6 ? 6 : 4) << " address: " << addrstr;
					if (res->ai_canonname != NULL)  ss << " (" << res->ai_canonname << ")";
					res = res->ai_next;
				}

				freeaddrinfo(origin);
				Logger::GetInstance().Info() << ss.str();
			}
		}
	}
}