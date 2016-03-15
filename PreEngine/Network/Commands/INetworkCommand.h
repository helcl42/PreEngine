/* 
 * File:   INetworkCommand.h
 * Author: lubos
 *
 * Created on July 1, 2015, 1:42 PM
 */

#ifndef INETWORKCOMMAND_H
#define	INETWORKCOMMAND_H

#include <json/json.h>

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Network
	{
		namespace Commands
		{
			class INetworkCommand
			{
			public:
				virtual void Execute(Json::Value root) = 0;

			public:
				virtual ~INetworkCommand() {}
			};
		}
	}
}

#endif	/* INETWORKCOMMAND_H */

