#ifndef FPS_SERVICE_H
#define FPS_SERVICE_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Time
		{
			using namespace PreEngine::Core;

			class FPSService
			{
			private:
				const int MAX_SNAPSHOTS_COUNT = 30;

				float refreshTimeout = 1.0f;

				std::vector<float> m_deltaTimeSnapshots;

				float m_elpasedTime = 0.0f;

				float m_averageDeltaTime = 0.0f;

			public:
				FPSService(float refreshTimeInS = 1.0f);

				virtual ~FPSService();

			public:
				void Update(float deltaTime);

				float GetAverageDeltaTime() const;

				float GetAverageFPS() const;
			};
		}
	}
}

#endif
