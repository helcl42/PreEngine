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
						for (unsigned int i = 0; i < 1000;)
						{
							if (m_isFinished) return;							

							std::this_thread::sleep_for(std::chrono::microseconds(m_msTimeout));

							if (!m_paused)
							{
								i++;
								m_elapsedMs += static_cast<long>(static_cast<double>(m_msTimeout) / 1000.0);
							}
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
					if (!m_forceStop)
					{
						const std::vector<ITimerObservable*>& observables = m_observer.GetObservables();
						for (std::vector<ITimerObservable*>::const_iterator ci = observables.cbegin(); ci != observables.cend(); ++ci)
						{
							(*ci)->OnTimerFinished();
						}
					}
				}

				void Timer::Start()
				{
					if (!m_isFinished) Stop();					
					m_forceStop = false;
					m_isFinished = false;
					m_elapsedMs = 0;
					RunThread();
				}

				void Timer::Pause()
				{
					m_paused = true;
				}

				void Timer::TogglePause()
				{
					m_paused = !m_paused;
				}

				void Timer::Stop()
				{
					m_forceStop = true;
					if (!m_isFinished) Join();
					m_isFinished = true;
					m_paused = false;
				}

				void Timer::SetMSTimeout(unsigned int timeout)
				{
					m_msTimeout = timeout;
				}

				unsigned int Timer::GetMSTimeout() const
				{
					return m_msTimeout;
				}

				long Timer::GetElapsedTimeInMS() const
				{
					if(IsActive()) return m_elapsedMs;
					return 0L;
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