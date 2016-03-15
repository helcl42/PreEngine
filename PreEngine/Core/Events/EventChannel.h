#ifndef EVENT_CHANNEL_H
#define EVENT_CHANNEL_H

#include "EventChannelQueue.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Events
		{
			class EventChannel
			{
			public:
				template <typename MessageType, typename EventHandlerType>
				static void Add(EventHandlerType* handler);

				template <typename MessageType, typename EventHandlerType>
				static void Remove(EventHandlerType* handler);

				template <typename MessageType>
				static void Broadcast(const MessageType& message);
			};


			template <typename MessageType, typename EventHandlerType>
			void EventChannel::Add(EventHandlerType* handler)
			{
				EventChannelQueue<MessageType>::GetInstance().Add(handler);
			}

			template <typename MessageType, typename EventHandlerType>
			void EventChannel::Remove(EventHandlerType* handler)
			{
				EventChannelQueue<MessageType>::GetInstance().Remove(handler);
			}

			template <typename MessageType>
			void EventChannel::Broadcast(const MessageType& message)
			{
				EventChannelQueue<MessageType>::GetInstance().Broadcast(message);
			}
		}
	}
}

#endif