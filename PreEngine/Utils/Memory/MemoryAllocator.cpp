#include "MemoryAllocator.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			template <class AllocatedType>
			IMemoryPool*  MemoryAllocator<AllocatedType>::s_pMemoryPool = NULL;
		}
	}
}