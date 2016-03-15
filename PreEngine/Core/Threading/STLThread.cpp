#include "STLThread.h"


namespace PreEngine
{
	namespace Core
	{
		namespace Threading
		{
			STLThread::STLThread()
			{
			}

			STLThread::~STLThread()
			{
				SAFE_DELETE(m_worker);
			}

			void STLThread::ThreadProc(void* thizzz)
			{
				STLThread* thizz = (STLThread*)thizzz;
				thizz->OnThreadStarted();
				thizz->ThreadProcedure();
				thizz->OnThreadFinished();
			}

			void STLThread::RunThread()
			{
				m_worker = new std::thread(&STLThread::ThreadProc, this);
			}

			bool STLThread::Join(unsigned int timeout)
			{
				m_isFinished = true;
				m_worker->join();
				return true;
			}

			bool STLThread::IsFinished() const
			{
				return m_isFinished;
			}

			void STLThread::SetFinished(bool finished)
			{
				m_isFinished = finished;
			}
		}
	}
}