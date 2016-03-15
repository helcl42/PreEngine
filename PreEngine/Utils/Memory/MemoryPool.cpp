#include "MemoryPool.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			MemoryPool::MemoryPool()
			{
				Reset();
			}

			MemoryPool::~MemoryPool()
			{
				Destroy();
			}

			bool MemoryPool::Init(unsigned int chunkSize, unsigned int numberOfChunks)
			{
				if (m_ppRawMemoryArray) Destroy();

				m_chunkSize = chunkSize;
				m_numberOfChunks = numberOfChunks;

				if (GrowMemoryArray()) return true;
				return false;
			}

			void MemoryPool::Destroy()
			{
				for (unsigned int i = 0; i < m_memoryArraySize; i++)
				{
					SAFE_DELETE_ARRAY(m_ppRawMemoryArray[i]);
				}
				SAFE_DELETE_ARRAY(m_ppRawMemoryArray);
			}

			void* MemoryPool::Allocate()
			{
				if (!m_pHead)
				{
					if (!m_isResizeAllowed) return NULL;
					if (!GrowMemoryArray()) return NULL;
				}

				unsigned char* pRetChunk = m_pHead;
				m_pHead = GetNext(m_pHead);
				return (pRetChunk + CHUNK_HEADER_SIZE);
			}

			void MemoryPool::Free(void* pMemory)
			{
				if (pMemory != NULL)
				{
					unsigned char* pBlock = ((unsigned char*)pMemory) - CHUNK_HEADER_SIZE;
					SetNext(pBlock, m_pHead);
					m_pHead = pBlock;
				}
			}

			void MemoryPool::Reset()
			{
				m_ppRawMemoryArray = NULL;
				m_pHead = NULL;
				m_memoryArraySize = 0;
				m_chunkSize = 0;
				m_numberOfChunks = 0;
				m_isResizeAllowed = true;
			}

			bool MemoryPool::GrowMemoryArray()
			{
				size_t sizeToAllocate = sizeof(unsigned char*) * (m_memoryArraySize + 1);
				unsigned char** ppNewMemArray = new unsigned char*[sizeToAllocate];

				if (!ppNewMemArray) return false;

				for (unsigned int i = 0; i < m_memoryArraySize; i++)
				{
					ppNewMemArray[i] = m_ppRawMemoryArray[i];
				}

				ppNewMemArray[m_memoryArraySize] = AllocateNewMemoryBlock();

				if (m_pHead)
				{
					unsigned char* pCurrentBlock = m_pHead;
					unsigned char* pNextBlock = GetNext(m_pHead);
					while (pNextBlock)
					{
						pCurrentBlock = pNextBlock;
						pNextBlock = GetNext(pNextBlock);
					}
					SetNext(pCurrentBlock, ppNewMemArray[m_memoryArraySize]);
				}
				else
				{
					m_pHead = ppNewMemArray[m_memoryArraySize];
				}

				if (m_ppRawMemoryArray) SAFE_DELETE_ARRAY(m_ppRawMemoryArray);

				m_ppRawMemoryArray = ppNewMemArray;
				m_memoryArraySize++;
				return true;
			}

			unsigned char* MemoryPool::AllocateNewMemoryBlock(void)
			{
				size_t blockSize = m_chunkSize + CHUNK_HEADER_SIZE;
				size_t sizeToAllocate = blockSize * m_numberOfChunks;

				unsigned char* pNewMemory = new unsigned char[sizeToAllocate];
				if (!pNewMemory) return NULL;

				unsigned char* pEnd = pNewMemory + sizeToAllocate;
				unsigned char* pCurrent = pNewMemory;
				while (pCurrent < pEnd)
				{
					unsigned char* pNext = pCurrent + blockSize;
					unsigned char** ppChunkHeader = (unsigned char**)pCurrent;
					ppChunkHeader[0] = (pNext < pEnd ? pNext : NULL);

					pCurrent += blockSize;
				}
				return pNewMemory;
			}

			unsigned char* MemoryPool::GetNext(unsigned char* pBlock)
			{
				unsigned char** ppChunkHeader = (unsigned char**)pBlock;
				return ppChunkHeader[0];
			}

			void MemoryPool::SetNext(unsigned char* pBlockToChange, unsigned char* pNext)
			{
				unsigned char** ppChunkHeader = (unsigned char**)pBlockToChange;
				ppChunkHeader[0] = pNext;
			}

			unsigned int MemoryPool::GetChunkSize() const
			{
				return m_chunkSize;
			}

			void MemoryPool::SetResizeAllowed(bool value)
			{
				this->m_isResizeAllowed = value;
			}

			bool MemoryPool::GetResizeAllowed() const
			{
				return m_isResizeAllowed;
			}
		}
	}
}