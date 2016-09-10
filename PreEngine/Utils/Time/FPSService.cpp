#include "FPSService.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			FPSService::FPSService(float refreshTimeInS)
				: refreshTimeout(refreshTimeInS)
			{
				m_deltaTimeSnapshots.resize(MAX_SNAPSHOTS_COUNT);
			}

			FPSService::~FPSService()
			{
			}

			void FPSService::Update(float deltaTime)
			{
				m_elpasedTime += deltaTime;

				m_deltaTimeSnapshots.push_back(deltaTime);

				if (m_deltaTimeSnapshots.size() > MAX_SNAPSHOTS_COUNT)
				{
					m_deltaTimeSnapshots.erase(m_deltaTimeSnapshots.begin(), m_deltaTimeSnapshots.begin() + (m_deltaTimeSnapshots.size() - MAX_SNAPSHOTS_COUNT));
				}

				if (m_elpasedTime > refreshTimeout)
				{
					float deltasSum = 0.0f;
					for (auto & snapshot : m_deltaTimeSnapshots)
					{
						deltasSum += snapshot;
					}
					m_averageDeltaTime = deltasSum / m_deltaTimeSnapshots.size();
					m_elpasedTime = 0.0f;

					//std::cout << "FPS: " << GetAverageFPS() << std::endl;
				}
			}

			float FPSService::GetAverageDeltaTime() const
			{
				return m_averageDeltaTime;
			}

			float FPSService::GetAverageFPS() const
			{
				if (m_averageDeltaTime > 0.0f)
				{
					return (1.0f / m_averageDeltaTime);
				}
				return 0.0f;
			}
		}
	}
}