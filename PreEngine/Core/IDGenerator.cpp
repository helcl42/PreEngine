#include "IDGenerator.h"

namespace PreEngine
{
	namespace Core
	{
		IDGenerator::IDGenerator()
		{
		}

		IDGenerator::~IDGenerator()
		{
		}

		uint64_t IDGenerator::GetNewId()
		{
			m_mutex.lock();
			m_identifier++;
			m_mutex.unlock();
			return m_identifier;
		}
	}
}