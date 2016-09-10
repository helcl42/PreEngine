#ifndef SYSTEM_H
#define SYSTEM_H

#include "Events/EventChannel.h"

namespace PreEngine
{
	namespace Core
	{
		using namespace PreEngine::Core::Events;

		class System
		{
		protected:
			EventChannel m_channel;

		private:
			System(const System&);

			System& operator=(const System&);

		public:
			System();

			virtual ~System();

		public:
			virtual bool Init() = 0;

			virtual void Update(float deltaTime) = 0;

			virtual void ShutDown() = 0;
		};
	}
}

#endif