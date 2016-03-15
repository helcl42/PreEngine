#ifndef MEMORY_UTIL_H
#define MEMORY_UTIL_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			using namespace PreEngine::Utils::Log;

			class MemoryUtil
			{
			public:
				static bool CheckMemory(const uint64_t physicalRAMNeeded, const uint64_t virtualRAMNeeded);

				static uint64_t GetAvailablePhysicalMemorySize();

				static uint64_t GetAvailableVirtualMemorySize();

				static uint64_t GetPhysicalMemorySize();
			};
		}
	}
}

#endif