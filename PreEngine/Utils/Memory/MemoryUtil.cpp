#include "MemoryUtil.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Memory
		{
			bool MemoryUtil::CheckMemory(const uint64_t physicalRAMNeeded, const uint64_t virtualRAMNeeded)
			{
				MEMORYSTATUSEX status;
				GlobalMemoryStatusEx(&status);

				if (status.ullTotalPhys < physicalRAMNeeded)
				{
					Logger::GetInstance().Info() << "CheckMemory Failure : Not enough physical memory.";
					return false;
				}

				if (status.ullAvailVirtual < virtualRAMNeeded)
				{
					Logger::GetInstance().Info() << "CheckMemory Failure : Not enough virtual memory.";
					return false;
				}

				char* buffer = new char[static_cast<unsigned int>(virtualRAMNeeded)];
				if (buffer)
				{
					SAFE_DELETE_ARRAY(buffer);
				}
				else
				{
					// memory is too fragmented
					Logger::GetInstance().Info() << "CheckMemory Failure : Not enough contiguous memory.";
					return false;
				}
				return true;
			}

			uint64_t MemoryUtil::GetAvailablePhysicalMemorySize()
			{
				MEMORYSTATUSEX status;
				GlobalMemoryStatusEx(&status);
				return status.ullAvailPhys;
			}

			uint64_t MemoryUtil::GetAvailableVirtualMemorySize()
			{
				MEMORYSTATUSEX status;
				GlobalMemoryStatusEx(&status);
				return status.ullAvailVirtual;
			}

			uint64_t MemoryUtil::GetPhysicalMemorySize()
			{
				MEMORYSTATUSEX status;
				GlobalMemoryStatusEx(&status);
				return status.ullTotalPhys;
			}
		}
	}
}