#ifndef CLOCK_H
#define CLOCK_H

#include "IClock.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Clocks
			{
				template <class Type>
				class Clock : public IClock <Type>
				{
				private:
					clock_t m_lastFrameTimestamp;

					Type m_frameInterval;

				public:
					Clock()
						: m_frameInterval(0.0f)
					{
					}

					virtual ~Clock() {}

				public:
					void Reset();

					void UpdateClock();

					Type SpeedOptimizedValue(Type val);

					Type GetDelta();
				};

				template <class Type>
				void Clock<Type>::Reset()
				{
					m_lastFrameTimestamp = clock();
					m_frameInterval = 0.0f;
				}

				template <class Type>
				Type Clock<Type>::SpeedOptimizedValue(Type val)
				{
					return m_lastFrameTimestamp * val;
				}

				template <class Type>
				void Clock<Type>::UpdateClock()
				{
					clock_t currentTimestamp = clock();
					m_frameInterval = Type(currentTimestamp - m_lastFrameTimestamp) / Type(CLOCKS_PER_SEC);
					m_lastFrameTimestamp = currentTimestamp;
				}

				template <class Type>
				Type Clock<Type>::GetDelta()
				{
					return m_frameInterval;
				}
			}
		}
	}
}

#endif