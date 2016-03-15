#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include "IMemoryPool.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			template <class AllocatedType>
			class MemoryAllocator
			{
			protected:
				static IMemoryPool* s_pMemoryPool;

			public:
				MemoryAllocator(unsigned int size = 10);
				virtual ~MemoryAllocator();

			public:
				void InitMemoryPool(unsigned int numChunks = 0);
				void DestroyMemoryPool(void);

			public:
				void* operator new (size_t size);
				void  operator delete(void* pPtr);
				void* operator new[](size_t size);
				void  operator delete[](void* pPtr);
			};

			template <class AllocatedType>
			MemoryAllocator<AllocatedType>::MemoryAllocator(unsigned int size)
			{
				InitMemoryPool(size);
			}

			template <class AllocatedType>
			MemoryAllocator<AllocatedType>::~MemoryAllocator()
			{
				SAFE_DELETE(s_pMemoryPool);
			}

			template <class AllocatedType>
			void MemoryAllocator<AllocatedType>::InitMemoryPool(unsigned int numChunks)
			{
				if (s_pMemoryPool != NULL) SAFE_DELETE(this->s_pMemoryPool);

				s_pMemoryPool = new MemoryPool();
				s_pMemoryPool->Init(sizeof(AllocatedType), numChunks);
			}

			template <class AllocatedType>
			void MemoryAllocator<AllocatedType>::DestroyMemoryPool(void)
			{
				SAFE_DELETE(s_pMemoryPool);
			}

			template <class AllocatedType>
			void* MemoryAllocator<AllocatedType>::operator new(size_t size)
			{
				void* pMem = s_pMemoryPool->Allocate();
				return pMem;
			}

				template <class AllocatedType>
			void MemoryAllocator<AllocatedType>::operator delete(void* pPtr)
			{
				s_pMemoryPool->Free(pPtr);
			}

			template <class AllocatedType>
			void* MemoryAllocator<AllocatedType>::operator new[](size_t size)
			{
				void* pMem = s_pMemoryPool->Allocate();
				return pMem;
			}

				template <class AllocatedType>
			void MemoryAllocator<AllocatedType>::operator delete[](void* pPtr)
			{
				s_pMemoryPool->Free(pPtr);
			}
		}
	}
}

#endif