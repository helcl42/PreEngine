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

		bool m_externalConfig = false;;

	private:
		void OnCreate();

	public:
		App(const std::string& configPath);

		App(ConfigType* config);

		virtual ~App();

	protected:
		virtual bool InitApp() = 0;

	public:
		virtual void Init(); // let it overridable

		virtual void Run(); // let it overridable
	};

	template <class ClientType, class EngineType, class ConfigType>
	App<ClientType, EngineType, ConfigType>::App(const std::string& configPath)
	{
		OnCreate();
		m_config = new ConfigType(configPath);
		m_engine = new EngineType(m_config);
		m_externalConfig = false;
	}

	template <class ClientType, class EngineType, class ConfigType>
	App<ClientType, EngineType, ConfigType>::App(ConfigType* config)
	{
		OnCreate();
		m_config = config;
		m_engine = new EngineType(m_config);
		m_externalConfig = true;
	}

	template <class ClientType, class EngineType, class ConfigType>
	App<ClientType, EngineType, ConfigType>::~App()
	{
		SAFE_DELETE(m_engine);
		if(!m_externalConfig) SAFE_DELETE(m_config);

		Logger::GetInstance().Info() << "App '" + GetName() + "' Finished";
	}

	template <class ClientType, class EngineType, class ConfigType>
	void App<ClientType, EngineType, ConfigType>::OnCreate()
	{
		Logger::GetInstance().SetOutputFileName(GetCanonicalName() + ".log");
		Logger::GetInstance().Info() << "App '" + GetName() + "' Started";

		m_state = AppState::NOT_INITIALIZED;
	}

	template <class ClientType, class EngineType, class ConfigType>
	void App<ClientType, EngineType, ConfigType>::Init()
	{
		if (m_state == AppState::INITIALIZED || m_state == AppState::ALREADY_RUN)
		{
			throw AppException("App is already initialized.");
		}

		bool result = InitApp();
		m_state = result ? AppState::INITIALIZED : AppState::NOT_INITIALIZED;
	}

	template <class ClientType, class EngineType, class ConfigType>
	void App<ClientType, EngineType, ConfigType>::Run()
	{
		if (!(m_state == AppState::INITIALIZED || m_state == AppState::ALREADY_RUN))
		{
			throw AppException("App has to be initizlied before calling Run().");
		}

		m_state = AppState::RUNNING;

		m_engine->Init();
		m_engine->MainLoop();
		m_engine->ShutDown();

		m_state = AppState::ALREADY_RUN;
	}
}

#endif