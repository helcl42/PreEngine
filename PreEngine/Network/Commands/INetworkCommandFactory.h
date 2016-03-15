/* 
 * File:   INetworkCommandFactory.h
 * Author: lubos
 *
 * Created on July 1, 2015, 1:41 PM
 */

#ifndef INETWORKCOMMANDFACTORY_H
#define	INETWORKCOMMANDFACTORY_H

#include "INetworkCommand.h"

namespace PreEngine
{
	namespace Network
	{
		namespace Commands
		{
			class INetworkCommandFactory
			{
			public:
				virtual void AddCommand(std::string key, INetworkCommand* command) = 0;

				virtual INetworkCommand* CreateCommand(std::string messageType) = 0;

			public:
				virtual ~INetworkCommandFactory() {}
			};
		}
	}
}

#endif	/* INETWORKCOMMANDFACTORY_H */

