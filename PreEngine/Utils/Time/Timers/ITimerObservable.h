/* 
 * File:   ITimerObservable.h
 * Author: lubos
 *
 * Created on July 3, 2015, 9:55 AM
 */

#ifndef ITIMERCLIENT_H
#define	ITIMERCLIENT_H

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Timers
			{
				class ITimerObservable
				{
				public:
					virtual void OnTimeout() = 0;

					virtual void OnTimerFinished() = 0;

				public:
					virtual ~ITimerObservable() {}
				};
			}
		}
	}
}

#endif	/* ITIMERCLIENT_H */

