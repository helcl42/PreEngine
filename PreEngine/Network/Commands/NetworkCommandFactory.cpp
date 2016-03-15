#include "NetworkCommandFactory.h"

namespace PreEngine
{
	namespace Network
	{
		namespace Commands
		{
			NetworkCommandFactory::NetworkCommandFactory()
			{
			}

			NetworkCommandFactory::~NetworkCommandFactory()
			{
				for (std::map<std::string, INetworkCommand*>::iterator mi = m_commmands.begin(); mi != m_commmands.end(); ++mi)
				{
					SAFE_DELETE(mi->second);
				}
			}

			void NetworkCommandFactory::AddCommand(std::string key, INetworkCommand* command)
			{
				m_commmands.insert(std::make_pair(key, command));
			}

			INetworkCommand* NetworkCommandFactory::CreateCommand(std::string messageType)
			{
				if (m_commmands.find(messageType) != m_commmands.cend())
				{
					INetworkCommand* command = m_commmands[messageType];
					return command;
				}
				return NULL;
			}
		}
	}
}
