/* 
 * File:   Timer.h
 * Author: lubos
 *
 * Created on July 3, 2015, 9:56 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#include "../../../Core/Common.h"
#include "../../../Core/Observer.h"
#include "../../../Core/Threading/Thread.h"

#include "ITimer.h"
#include "ITimerObservable.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Timers
			{
				using namespace PreEngine::Core;
				using namespace PreEngine::Core::Threading;
				using namespace PreEngine::Utils::Log;

				class Timer : public Thread, public ITimer
				{
				private:
					unsigned int m_msTimeout = 1000;

					bool m_runOnce = false;

					Observer<ITimerObservable> m_observer;

				public:
					Timer(bool runOnceOnly);

					Timer(unsigned int msTimeout, bool runOnceOnly);

					virtual ~Timer();

				protected:
					void OnThreadStarted();

					void ThreadProcedure();

					void OnThreadFinished();

				public:
					void Start();

					void Stop();

					void SetMsTimeout(unsigned int timeout);

					bool IsActive() const;

					bool RegisterListener(ITimerObservable* listener);

					bool UnregisterListener(ITimerObservable* listener);
				};
			}
		}
	}
}

#endif	/* TIMER_H */

