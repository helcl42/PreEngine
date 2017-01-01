#include "AbstractEngine.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			AbstractEngine::AbstractEngine(EngineConfig* config)
				: m_config(config)
			{
				m_clock = new Clock<float>();
				m_input = new Input();
				m_audioContext = new AudioContext();
			}

			AbstractEngine::~AbstractEngine()
			{
				SAFE_DELETE(m_audioContext);
				SAFE_DELETE(m_clock);
				SAFE_DELETE(m_input);
			}

			Input* AbstractEngine::GetInput() const
			{
				return m_input;
			}

			IClock<float>* AbstractEngine::GetClock() const
			{
				return m_clock;
			}

			EngineConfig* AbstractEngine::GetConfig() const
			{
				return m_config;
			}

			AudioContext* AbstractEngine::GetAudioContext() const
			{
				return m_audioContext;
			}

			void AbstractEngine::operator()(const OnEngineShutDownRequest& shutDownRequest)
			{
				m_finishRequested = true;
			}
		}
	}
}