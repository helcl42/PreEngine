#ifndef STL_THREAD_H
#define STL_THREAD_H

#include "../Common.h"
#include "IThread.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Threading
		{
			class STLThread : public IThread
			{
			private:
				static void ThreadProc(void* thizzz);

				std::thread* m_worker = NULL;

			protected:
				virtual void OnThreadStarted() = 0;

				virtual void ThreadProcedure() = 0;

				virtual void OnThreadFinished() = 0;

			protected:
				bool m_isFinished;

			public:
				STLThread();

				virtual ~STLThread();

			public:
				void RunThread();

				bool Join(unsigned int timeout);

				bool IsFinished() const;

				void SetFinished(bool finished);
			};
		}
	}
}

#endif