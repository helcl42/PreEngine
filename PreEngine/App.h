#ifndef APP_H
#define APP_H

#include "Core/Common.h"
#include "Core/Engines/Engine.h"
#include "Core/Object.h"

#include "AppException.h"

namespace PreEngine
{
	using namespace PreEngine::Core;
	using namespace PreEngine::Core::Engines;
	using namespace PreEngine::Core::Engines::Config;

	using namespace PreEngine::Utils::Log;

	template <class ClientType, class EngineType, class ConfigType>
	class App : public Object<ClientType>
	{
	protected:
		enum AppState
		{
			NOT_INITIALIZED = 0,
			INITIALIZED,
			RUNNING,
			ALREADY_RUN
		};

		ConfigType* m_config;

		EngineType* m_engine;

		AppState m_state;

	public:
		App(const std::string& configPath);

		virtual ~App();

	protected:
		virtual void InitApp() = 0;

	public:
		void Init();

		virtual void Run(); // let it overridable
	};

	template <class ClientType, class EngineType, class ConfigType>
	App<ClientType, EngineType, ConfigType>::App(const std::string& configPath)
	{
		Logger::GetInstance().SetOutputFileName(GetCanonicalName() + ".log");
		Logger::GetInstance().Info() << "App '" + GetName() + "' Started";

		m_state = AppState::NOT_INITIALIZED;

		m_config = new ConfigType(configPath);
		m_engine = new EngineType(m_config);
	}


	template <class ClientType, class EngineType, class ConfigType>
	App<ClientType, EngineType, ConfigType>::~App()
	{
		SAFE_DELETE(m_engine);
		SAFE_DELETE(m_config);

		Logger::GetInstance().Info() << "App '" + GetName() + "' Finished";
	}

	template <class ClientType, class EngineType, class ConfigType>
	void App<ClientType, EngineType, ConfigType>::Init()
	{
		InitApp();
		m_state = INITIALIZED;
	}

	template <class ClientType, class EngineType, class ConfigType>
	void App<ClientType, EngineType, ConfigType>::Run()
	{
		if (!(m_state == AppState::INITIALIZED || m_state == AppState::ALREADY_RUN))
		{
			throw AppException("App has to initizlied: Call Init before Run().");
		}

		m_state = AppState::RUNNING;

		m_engine->Init();
		m_engine->MainLoop();
		m_engine->ShutDown();

		m_state = AppState::ALREADY_RUN;
	}
}

#endif