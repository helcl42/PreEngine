#ifndef ICLOCK_H
#define ICLOCK_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Clocks
			{
				template <class Type>
				class IClock
				{
				public:
					virtual void Reset() = 0;

					virtual void UpdateClock() = 0;

					virtual Type SpeedOptimizedValue(Type val) = 0;

					virtual Type GetDelta() = 0;

				public:
					virtual ~IClock() {}
				};
			}
		}
	}
}

#endif