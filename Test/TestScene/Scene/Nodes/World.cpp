#include "World.h"

namespace TestScene
{
	namespace Nodes
	{
		World::World()
			: BaseSceneNode<World, World>(this),
			m_isInWireframeMode(false)
		{
			m_inputFacade = new InputFacade();
			m_inputFacade->RegisterKeyboardListener(this);

			m_shadowsSceneNode = new ShadowsSceneNode<World>(this);
			AddChild(m_shadowsSceneNode);
			m_camera = new CameraSceneNode<World>(this);
			AddChild(m_camera);
			m_skybox = new SkyboxSceneNode<World>(this);
			AddChild(m_skybox);
			m_terrain = new TerrainSceneNode<World>(this, "./TestScene/Assets/Worlds/height_map_2.bmp");
			AddChild(m_terrain);
			m_sun = new SunSceneNode<World>(this);
			AddChild(m_sun);
			m_stoneGarage = new StoneGarageSceneNode<World>(this);
			AddChild(m_stoneGarage);
			m_runins = new RuinsSceneNode<World>(this);
			AddChild(m_runins);
			m_army = new ArmySceneNode<World>(this, "./TestScene/Assets/Models/blade/Blade.md2");
			AddChild(m_army);
			m_mainActor = new MainActorSceneNode<World>(this);
			AddChild(m_mainActor);	
			m_guard = new GuardSceneNode<World>(this, "./TestScene/Assets/Models/guard/boblampclean.md5mesh");
			AddChild(m_guard);
			m_particleSystem = new ParticlesSceneNode<World>(this);
			AddChild(m_particleSystem);

			m_postProcess = new PostProcessSceneNode<World>(this);
			m_textViewer = new TextSceneNode<World>(this, "C:/Windows/Fonts/arial.ttf", 48);
		}

		World::~World()
		{
			SAFE_DELETE(m_textViewer);
			SAFE_DELETE(m_postProcess);
			SAFE_DELETE(m_particleSystem);
			SAFE_DELETE(m_guard);
			SAFE_DELETE(m_mainActor);
			SAFE_DELETE(m_army);
			SAFE_DELETE(m_runins);
			SAFE_DELETE(m_stoneGarage);
			SAFE_DELETE(m_sun);
			SAFE_DELETE(m_terrain);
			SAFE_DELETE(m_skybox);		
			SAFE_DELETE(m_camera);
			SAFE_DELETE(m_shadowsSceneNode);
			SAFE_DELETE(m_windowSound);
			SAFE_DELETE(m_inputFacade);			
		}

		void World::Init()
		{
			for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
			{
				(*ci)->Init();
			}

			m_postProcess->Init();
			m_textViewer->Init();

			m_shinyMaterial = Material(1.0f, 32.0f);

			SoundFactory soundFactory;
			m_windowSound = soundFactory.CreateSoundFromWav("./TestScene/Assets/Audio/wind.wav");
			m_windowSound->Play(1.0f, true);
		}

		std::string World::GetInfo() const
		{
			std::stringstream ss;
			ss << m_camera->GetInfo();
			ss << "Polygon Mode: " << (m_isInWireframeMode ? "Wireframe" : "Normal") << std::endl;
			ss << "Normals: " << (m_showNormals ? "ON" : "OFF") << std::endl;
			ss << "Normal Length: " << m_normalLength << std::endl;
			ss << "---------------------------------------" << std::endl;
			ss << m_sun->GetInfo();
			ss << "Specular Light Intensity: " << m_shinyMaterial.GetSpecularIntensity() << std::endl;
			ss << "Specular Light Power: " << m_shinyMaterial.GetSpecularPower() << std::endl;
			ss << "---------------------------------------" << std::endl;
			ss << m_particleSystem->GetInfo();
			ss << m_mainActor->GetInfo();
			ss << "Bump Maps: " << (m_useBumpMaps ? "ON" : "OFF") << std::endl;
			ss << "---------------------------------------" << std::endl;
			ss << m_shadowsSceneNode->GetInfo();
			ss << m_postProcess->GetInfo();
			return std::string(ss.str());
		}

		void World::Update(float deltaTime)
		{
			m_deltaTime = deltaTime;

			if (m_inputFacade->IsKeyPressed(GLFW_KEY_G)) m_normalLength += 0.5f * deltaTime;
			if (m_inputFacade->IsKeyPressed(GLFW_KEY_H)) m_normalLength -= 0.5f * deltaTime;

			if (m_inputFacade->IsKeyPressed(GLFW_KEY_K)) m_shinyMaterial.SetSpecularIntensity(m_shinyMaterial.GetSpecularIntensity() + 0.1f * deltaTime);
			if (m_inputFacade->IsKeyPressed(GLFW_KEY_L)) m_shinyMaterial.SetSpecularIntensity(m_shinyMaterial.GetSpecularIntensity() - 0.1f * deltaTime);

			if (m_inputFacade->IsKeyPressed(GLFW_KEY_N)) m_shinyMaterial.SetSpecularPower(m_shinyMaterial.GetSpecularPower() + 0.001f * deltaTime);
			if (m_inputFacade->IsKeyPressed(GLFW_KEY_M)) m_shinyMaterial.SetSpecularPower(m_shinyMaterial.GetSpecularPower() - 0.001f * deltaTime);

			for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
			{
				(*ci)->Update(deltaTime);
			}

			m_postProcess->Update(deltaTime);
			m_textViewer->Update(deltaTime);

			TextData controlData(GetInfo(), 20, m_height - 30, 18, glm::vec4(1.0, 1.0, 1.0, 1.0));
			m_textViewer->AddMessage(controlData);

			m_fpsService.Update(deltaTime);

			std::stringstream ss;
			ss << int(m_fpsService.GetAverageFPS()) << " FPS / " << std::fixed << std::setprecision(3) << m_fpsService.GetAverageDeltaTime() << std::endl;
			TextData fpsMessage(ss.str(), m_width - m_textViewer->GetTextWidth(ss.str(), 18) - 20, 20, 18, glm::vec4(1.0, 1.0, 1.0, 1.0));
			m_textViewer->AddMessage(fpsMessage);
		}

		void World::PreRender()
		{
			if (m_isInWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			m_view = RenderUtil::GetViewMatrix(m_sun->GetSunLight().GetDirection(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			m_projection = RenderUtil::GetPerspectiveProjectionMatrix(m_width, m_height, 66.0f, 0.1f, 1000.0f);
			m_lightProjectionViewMatrix = RenderUtil::GetDepthBiasMatrix() * m_projection * m_view;

			EventChannel::Broadcast(RenderStateChangeEvent{ RenderPassType::SHADOW, m_projection, m_view, m_lightProjectionViewMatrix, m_useBumpMaps, m_showNormals, m_normalLength, m_shinyMaterial });

			for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
			{
				(*ci)->PreRender();
			}
		}

		void World::Render()
		{
			m_view = m_camera->GetCamera()->LookAt();
			m_projection = m_perspectiveProjectionMatrix;

			EventChannel::Broadcast(RenderStateChangeEvent{ RenderPassType::NORMAL, m_projection, m_view, m_lightProjectionViewMatrix, m_useBumpMaps, m_showNormals, m_normalLength, m_shinyMaterial });

			if(!m_isInWireframeMode) m_postProcess->PreRender();

			for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
			{
				(*ci)->Render();
			}
		}

		void World::PostRender()
		{
			if (m_showNormals)
			{
				m_view = m_camera->GetCamera()->LookAt();
				m_projection = m_perspectiveProjectionMatrix;

				EventChannel::Broadcast(RenderStateChangeEvent{ RenderPassType::NORMALS_ONLY, m_projection, m_view, m_lightProjectionViewMatrix, m_useBumpMaps, m_showNormals, m_normalLength, m_shinyMaterial });

				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->PostRender();
				}
			}

			if (!m_isInWireframeMode) m_postProcess->PostRender();
			m_textViewer->Render();
		}

		void World::ShutDown()
		{
			m_textViewer->ShutDown();
			m_postProcess->ShutDown();

			for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
			{
				(*ci)->ShutDown();
			}

			m_windowSound->Stop();
		}

		void World::OnKeyPressedHandler(const OnKeyPress& press)
		{
			if (press.key == GLFW_KEY_1) m_shadowsSceneNode->GetShadows()->ToggleShadowsOn();
			if (press.key == GLFW_KEY_2) m_shadowsSceneNode->GetShadows()->ToggleUsehardShadows();
			if (press.key == GLFW_KEY_E) m_isInWireframeMode = !m_isInWireframeMode;
			if (press.key == GLFW_KEY_T) m_showNormals = !m_showNormals;
			if (press.key == GLFW_KEY_C) m_useBumpMaps = !m_useBumpMaps;
		}

		void World::OnKeyReleasedHandler(const OnKeyRelease& release)
		{
		}
	}
}