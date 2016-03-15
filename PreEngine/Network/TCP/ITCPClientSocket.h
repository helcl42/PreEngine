/* 
 * File:   ITCPClientSocket.h
 * Author: lubos
 *
 * Created on July 1, 2015, 9:53 AM
 */

#ifndef ITCPCLIENTSOCKET_H
#define	ITCPCLIENTSOCKET_H

namespace PreEngine
{
	namespace Network
	{
		namespace TCP
		{
			class ITCPClientSocket
			{
			public:
				virtual bool Open() = 0;

				virtual bool IsOpen() = 0;

				virtual void Close() = 0;

				virtual SOCKET GetSocket() const = 0;

			public:
				virtual ~ITCPClientSocket() {}
			};
		}
	}
}

#endif	/* ITCPCLIENTSOCKET_H */

