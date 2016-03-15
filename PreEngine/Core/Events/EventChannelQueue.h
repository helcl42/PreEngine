#ifndef EVENT_CHANNEL_QUEUE_H
#define EVENT_CHANNEL_QUEUE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
#include <utility>

namespace PreEngine
{
	namespace Core
	{
		namespace Events
		{
			template <typename EventType>
			class EventChannelQueue
			{
			private:
				static EventChannelQueue s_instance;

			private:
				std::mutex m_mutex;

				std::vector<std::function<void(const EventType&)>> m_handlers;

				std::vector<void*> m_originalPointers;

			public:
				static EventChannelQueue& GetInstance();

				template <typename EventHandlerType> 
				void Add(EventHandlerType* handler);

				template <typename EventHandlerType>
				void Remove(EventHandlerType* handler);

				void Broadcast(const EventType& message);

			private:
				EventChannelQueue();

				virtual ~EventChannelQueue();

				template <typename EventHandlerType>
				std::function<void(const EventType&)> CreateHandler(EventHandlerType* handler);
			};


			template <typename EventType>
			EventChannelQueue<EventType> EventChannelQueue<EventType>::s_instance;

			template <typename EventType>
			EventChannelQueue<EventType>& EventChannelQueue<EventType>::GetInstance()
			{
				return s_instance;
			}

			template <typename EventType>
			EventChannelQueue<EventType>::EventChannelQueue()
			{
			}

			template <typename EventType>
			EventChannelQueue<EventType>::~EventChannelQueue()
			{
			}

			template <typename EventType>
			template <typename EventHandlerType>
			void EventChannelQueue<EventType>::Add(EventHandlerType* handler)
			{
				std::lock_guard<std::mutex> lock(m_mutex);

				m_handlers.push_back(CreateHandler(handler));
				m_originalPointers.push_back(handler);
			}

			template <typename EventType>
			template <typename EventHandlerType>
			void EventChannelQueue<EventType>::Remove(EventHandlerType* handler)
			{
				std::lock_guard<std::mutex> lock(m_mutex);

				auto it = std::find(m_originalPointers.begin(), m_originalPointers.end(), handler);
				if (it == m_originalPointers.end()) throw std::runtime_error("Tried to remove a handler that is not in the list");

				auto idx = (it - m_originalPointers.begin());

				m_handlers.erase(m_handlers.begin() + idx);
				m_originalPointers.erase(it);
			}

			template <typename EventType>
			void EventChannelQueue<EventType>::Broadcast(const EventType& message)
			{
				std::vector<std::function<void(const EventType&)>> localVector(m_handlers.size());

				{
					std::lock_guard<std::mutex> lock(m_mutex);
					localVector = m_handlers;
				}

				for (const auto& handler : localVector)
				{
					handler(message);
				}
			}

			template <typename EventType>
			template <typename EventHandlerType>
			std::function<void(const EventType&)> EventChannelQueue<EventType>::CreateHandler(EventHandlerType* handler)
			{
				return [handler](const EventType& message) { (*handler)(message); };
			}
		}
	}
}

#endif