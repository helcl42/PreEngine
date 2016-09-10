#ifndef UID_GENERATOR_H
#define UID_GENERATOR_H

#include "Common.h"

namespace PreEngine
{
	namespace Core
	{
		using namespace PreEngine::Core::Patterns;

		class IDGenerator : public Singleton<IDGenerator>
		{
		private:
			friend Singleton<IDGenerator>;

		private:			
			std::mutex m_mutex;

			uint64_t m_identifier = 0;

		private:
			IDGenerator();

		public:
			virtual ~IDGenerator();

		public:
			uint64_t GetNewId();
		};
	}
}


#endif // !UID_GENERATOR_H
