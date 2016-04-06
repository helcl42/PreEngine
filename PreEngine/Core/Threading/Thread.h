#ifndef THREAD_H
#define THREAD_H

#include "../Common.h"
#include "IThread.h"

#ifdef _WIN32
#include <Windows.h> 
#include <process.h>
#else
#include <pthread.h>
#endif

namespace PreEngine
{
	namespace Core
	{
		namespace Threading
		{
			class Thread : public IThread
			{
			private:
				static void ThreadProc(void* thizzz);

#ifdef _WIN32
				HANDLE m_threadHandle = INVALID_HANDLE_VALUE;
#else
				pthread_t m_threadHandle;
				pthread_attr_t m_threadAttr;
#endif

			protected:
				virtual void OnThreadStarted() = 0;

				virtual void ThreadProcedure() = 0;

				virtual void OnThreadFinished() = 0;

			protected:
				bool m_isFinished;

			public:
				Thread();

				virtual ~Thread();

			public:
				void RunThread();

				bool Join(unsigned int timeout = 2000);

				bool IsFinished() const;

				void SetFinished(bool finished);
			};
		}
	}
}

#endif