#ifndef ITIMER_H
#define	ITIMER_H

#include "ITimerObservable.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Timers
			{
				class ITimer
				{
				public:
					virtual void Start() = 0;

					virtual void Stop() = 0;

					virtual bool RegisterListener(ITimerObservable* listener) = 0;

					virtual bool UnregisterListener(ITimerObservable* listener) = 0;

					virtual void SetMsTimeout(unsigned int timeout) = 0;

					virtual bool IsActive() const = 0;

				public:
					virtual ~ITimer() {}
				};
			}
		}
	}
}

#endif	/* ITIMER_H */
