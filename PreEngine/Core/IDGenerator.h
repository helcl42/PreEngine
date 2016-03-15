#ifndef UID_GENERATOR_H
#define UID_GENERATOR_H

#include "Common.h"

namespace PreEngine
{
	namespace Core
	{
		class IDGenerator
		{
		private:
			static IDGenerator s_instance;

			std::mutex m_mutex;

			uint64_t m_identifier = 0;

		private:
			IDGenerator();

		public:
			static IDGenerator& GetInstance();

			virtual ~IDGenerator();

		public:
			uint64_t GetNewId();
		};
	}
}


#endif // !UID_GENERATOR_H
