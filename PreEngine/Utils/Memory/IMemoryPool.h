#ifndef IMEMORY_POOL_H
#define IMEMORY_POOL_H

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			class IMemoryPool
			{
			public:
				virtual bool Init(unsigned int chunkSize, unsigned int numberOfChunks) = 0;

				virtual void Destroy() = 0;

				virtual void* Allocate() = 0;

				virtual void Free(void* pMemory) = 0;

				virtual unsigned int GetChunkSize() const = 0;

				virtual void SetResizeAllowed(bool value) = 0;

				virtual bool GetResizeAllowed() const = 0;
			};
		}
	}
}

#endif