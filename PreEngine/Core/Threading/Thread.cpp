#include "Thread.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Threading
		{
			Thread::Thread()
			{
			}

			Thread::~Thread()
			{
			}

			void Thread::ThreadProc(void* thizzz)
			{
				Thread* thizz = (Thread*)thizzz;
				thizz->OnThreadStarted();
				thizz->ThreadProcedure();
				thizz->OnThreadFinished();
#ifdef _WIN32
				_endthreadex(0);
#endif
			}

			void Thread::RunThread()
			{
#ifdef _WIN32
				m_threadHandle = (HANDLE)_beginthread(&Thread::ThreadProc, 0, this);
#else
				pthread_attr_init(&m_attr);
				pthread_attr_setdetachstate(&m_threadAttr, PTHREAD_CREATE_JOINABLE);
				pthread_create(&m_threadHandle, &m_attr, threadProcedure, this);
#endif
			}

			bool Thread::Join(unsigned int timeout)
			{
				m_isFinished = true;
#ifdef _WIN32
				if (WaitForSingleObject(m_threadHandle, timeout) != WAIT_OBJECT_0)
				{
					if (m_threadHandle != INVALID_HANDLE_VALUE) CloseHandle(m_threadHandle);
					return false;
				}
				m_threadHandle = INVALID_HANDLE_VALUE;
				return true;
#else
				int rcCount = pthread_join(m_threadHandle, NULL);
				pthread_attr_destroy(&m_threadAttr);
				return rcCount == 0;
#endif
			}

			bool Thread::IsFinished() const
			{
				return m_isFinished;
			}

			void Thread::SetFinished(bool finished)
			{
				m_isFinished = finished;
			}
		}
	}
}