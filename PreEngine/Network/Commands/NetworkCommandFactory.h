/* 
 * File:   NetworkCommandFactory.h
 * Author: lubos
 *
 * Created on July 1, 2015, 1:23 PM
 */

#ifndef NETWORKCOMMANDFACTORY_H
#define	NETWORKCOMMANDFACTORY_H

#include "../../Core/Common.h"
#include "INetworkCommandFactory.h"

#include "INetworkCommand.h"

namespace PreEngine
{
	namespace Network
	{
		namespace Commands
		{
			class NetworkCommandFactory : public INetworkCommandFactory
			{
			private:
				std::map<std::string, INetworkCommand*> m_commmands;

			public:
				NetworkCommandFactory();

				virtual ~NetworkCommandFactory();

			public:
				void AddCommand(std::string key, INetworkCommand* command);

				INetworkCommand* CreateCommand(std::string messageType);
			};
		}
	}
}

#endif	/* NETWORKCOMMANDFACTORY_H */

