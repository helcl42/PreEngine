#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "../../Core/Common.h"
#include "IMemoryPool.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			class MemoryPool : public IMemoryPool
			{
			private:
				unsigned char** m_ppRawMemoryArray;

				unsigned int m_memoryArraySize;

				unsigned char* m_pHead;

				unsigned int m_chunkSize;

				unsigned int m_numberOfChunks;

				bool m_isResizeAllowed;

				const static size_t CHUNK_HEADER_SIZE = (sizeof(unsigned char*));

			public:
				MemoryPool();

				~MemoryPool();

			private:
				MemoryPool(const MemoryPool& other) {}

				MemoryPool& operator=(const MemoryPool& other) {}

			public:
				bool Init(unsigned int chunkSize, unsigned int numberOfChunks);

				void Destroy();

				void* Allocate();

				void Free(void* pMemory);

				unsigned int GetChunkSize() const;

				void SetResizeAllowed(bool value);

				bool GetResizeAllowed() const;

			private:
				void Reset();

				bool GrowMemoryArray();

				unsigned char* AllocateNewMemoryBlock(void);

				unsigned char* GetNext(unsigned char* pBlock);

				void SetNext(unsigned char* pBlockToChange, unsigned char* pNext);
			};
		}
	}
}

#endif
