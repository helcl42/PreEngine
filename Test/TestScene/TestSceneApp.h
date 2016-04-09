#ifndef TEST_SCENE_APP_H
#define TEST_SCENE_APP_H

#include <PreEngine/Core/Common.h>
#include <PreEngine/App.h>

#include "Scene/Nodes/World.h"

namespace TestScene
{
	using namespace PreEngine;
	using namespace TestScene::Nodes;

	class TestSceneApp : public App<TestSceneApp, Engine<World>, EngineConfig>
	{
	public:
		TestSceneApp(const std::string& configPath)
			: App<TestSceneApp, Engine<World>, EngineConfig>(configPath)
		{
		}

		virtual ~TestSceneApp()
		{
		}

		bool InitApp()
		{
			IScene<World>* scene = m_engine->GetScene();
			scene->AddSceneNode(new World());
			return true;
		}
	};
}

#endif