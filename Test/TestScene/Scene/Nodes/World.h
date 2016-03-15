#ifndef WORLD_H
#define WORLD_H

#include <PreEngine/Render/Lightning/Material.h>
#include <PreEngine/Inputs/InputFacade.h>
#include <PreEngine/Utils/Render/RenderUtil.h>
#include <PreEngine/Audio/SoundFactory.h>

#include "BaseSceneNode.h"
#include "Skybox/SkyboxSceneNode.h"
#include "Text/TextSceneNode.h"
#include "Particles/ParticlesSceneNode.h"
#include "Terrain/TerrainSceneNode.h"
#include "Sun/SunSceneNode.h"
#include "Buildings/StoneGarageSceneNode.h"
#include "Buildings/RuinsSceneNode.h"
#include "Actors/ArmySceneNode.h"
#include "Actors/MainActorSceneNode.h"
#include "Shadows/ShadowsSceneNode.h"
#include "Cameras/CameraSceneNode.h"
#include "PostProcess/PostProcessSceneNode.h"
#include "Actors/GuardSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Lightning;
		using namespace PreEngine::Render::FrameBuffers;
		using namespace PreEngine::Utils::Render;
		using namespace PreEngine::Inputs;
		using namespace PreEngine::Audio;

		class World : public BaseSceneNode<World, World>, public IKeyboardListener
		{
		private:
			bool m_isInWireframeMode;

			IInputFacade* m_inputFacade;

			Material m_shinyMaterial;

			ISound* m_windowSound;

			CameraSceneNode<World>* m_camera;

			ShadowsSceneNode<World>* m_shadowsSceneNode;

			SkyboxSceneNode<World>* m_skybox;

			TextSceneNode<World>* m_textViewer;

			ParticlesSceneNode<World>* m_particleSystem;

			TerrainSceneNode<World>* m_terrain;

			SunSceneNode<World>* m_sun;

			StoneGarageSceneNode<World>* m_stoneGarage;

			RuinsSceneNode<World>* m_runins;

			ArmySceneNode<World>* m_army;

			MainActorSceneNode<World>* m_mainActor;

			GuardSceneNode<World>* m_guard;

			PostProcessSceneNode<World>* m_postProcess;

		public:
			World();

			virtual ~World();

		public:
			void Init();

			std::string GetInfo() const;

			void Update(float deltaTime);

			void PreRender();

			void Render();

			void PostRender();

			void ShutDown();

		public:
			void OnKeyPressedHandler(const OnKeyPress& press);

			void OnKeyReleasedHandler(const OnKeyRelease& release);
		};
	}
}
#endif