#ifndef ABSTRACT_ENGINE_H
#define ABSTRACT_ENGINE_H

#include "../Common.h"

#include "../../Render/Scene.h"
#include "../../Render/DoubleScene.h"

#include "../System.h"

#include "../../Inputs/Core/Input.h"
#include "../../Utils/Time/Clocks/Clock.h"

#include "../../Windows/GLWindow.h"

#include "../../Audio/AudioContext.h"

#include "Config/EngineConfig.h"
#include "EngineException.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Inputs::Core;
			using namespace PreEngine::Audio;
			using namespace PreEngine::Core::Engines::Config;

			using namespace PreEngine::Utils::Time::Clocks;

			class AbstractEngine
			{
			protected:
				Input* m_input;

				IClock<float>* m_clock;

				bool  m_unlimitedLoop;

				const float FIXED_FRAME_PERIOD = 1.0f / 60.0f;

				EngineConfig* m_config;

				AudioContext* m_audioContext;

			public:
				AbstractEngine(EngineConfig* config);

				virtual ~AbstractEngine();

			public:

				virtual void Init() = 0;

				virtual void MainLoop() = 0;

				virtual void ShutDown() = 0;

			public:
				Input* GetInput() const;

				IClock<float>* GetClock() const;

				EngineConfig* GetConfig() const;

				AudioContext* GetAudioContext() const;
			};
		}
	}
}

#endif