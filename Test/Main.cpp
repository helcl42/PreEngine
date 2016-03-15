#include "TestScene/TestSceneApp.h"

int main(int argc, char** argv)
{
	TestScene::TestSceneApp testSceneApp("./TestScene/Assets/Configs/Config.json");
	testSceneApp.Init();
	testSceneApp.Run();

	return 0;
}