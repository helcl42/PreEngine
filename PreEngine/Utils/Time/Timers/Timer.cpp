#include "Timer.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			namespace Timers
			{
				Timer::Timer(bool runOnceOnly)
					: m_runOnce(runOnceOnly)
				{
				}

				Timer::Timer(unsigned int msTimeout, bool runOnceOnly)
					: m_msTimeout(msTimeout), m_runOnce(runOnceOnly)
				{
				}

				Timer::~Timer()
				{
				}

				void Timer::OnThreadStarted()
				{
				}

				void Timer::ThreadProcedure()
				{
					while (!m_isFinished)
					{
						for (unsigned int i = 0; i < 1000; i++)
						{
							if (m_isFinished) return;
							std::this_thread::sleep_for(std::chrono::microseconds(m_msTimeout));
						}

						const std::vector<ITimerObservable*>& observables = m_observer.GetObservables();
						for (std::vector<ITimerObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
						{
							(*ci)->OnTimeout();
						}

						if (m_runOnce) m_isFinished = true;
					}
				}

				void Timer::OnThreadFinished()
				{
					const std::vector<ITimerObservable*>& observables = m_observer.GetObservables();
					for (std::vector<ITimerObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
					{
						(*ci)->OnTimerFinished();
					}
				}

				void Timer::Start()
				{
					if (m_isFinished) Stop();
					m_isFinished = false;
					RunThread();
				}

				void Timer::Stop()
				{					
					if(!m_isFinished) Join();
					m_isFinished = true;
				}

				void Timer::SetMsTimeout(unsigned int timeout)
				{
					m_msTimeout = timeout;
				}

				bool Timer::IsActive() const
				{
					return !m_isFinished;
				}

				bool Timer::RegisterListener(ITimerObservable* listener)
				{
					return m_observer.RegisterListener(listener);
				}

				bool Timer::UnregisterListener(ITimerObservable* listener)
				{
					return m_observer.RegisterListener(listener);
				}

			}
		}
	}
}