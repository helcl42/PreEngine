#ifndef PARTICLES_SCENE_NODE_H
#define PARTICLES_SCENE_NODE_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/Particles/ParticleSystemTransformFeedback.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Particles;
		using namespace PreEngine::Inputs;

		template <class RootType>
		class ParticlesSceneNode : public BaseSceneNode<ParticlesSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			const float POSITION_STEP = 0.5f;

			const float VELOCITY_STEP = 0.5f;

			const float GRAVITY_STEP = 0.2f;

			const float COLOR_STEP = 0.1f;

			const float SIZE_STEP = 0.2f;


			ParticleSystemTransformFeedback* m_particleSystem;

			ParticleSystemTransformFeedbackSettings m_particleSettings;

			ITexture* m_particleTexture;

			ITextureFactory* m_textureFactory;

			IInputFacade* m_inputFacade;

		public:
			ParticlesSceneNode(RootType* root)
				: BaseSceneNode<ParticlesSceneNode<RootType>, RootType>(root)
			{
				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);

				m_particleSystem = new ParticleSystemTransformFeedback();

				m_textureFactory = new TextureFactory();
			}

			virtual ~ParticlesSceneNode()
			{
				SAFE_DELETE(m_particleTexture);
				SAFE_DELETE(m_particleSystem);
				SAFE_DELETE(m_textureFactory);
				SAFE_DELETE(m_inputFacade);
			}

		private:
			void InitSettings()
			{
				m_particleSettings.genPosition = glm::vec3(-120.0f, 37.0f, -33.0f);	// position
				m_particleSettings.genVelocityMin = glm::vec3(-5.0f, 0.0f, -5.0f);	// min velocity
				m_particleSettings.genVelocityMax = glm::vec3(5.0f, 20.0f, 5.0f);	// max velocity
				m_particleSettings.genGravity = glm::vec3(0.0f, -5.0f, 0.0f);		// gravity
				m_particleSettings.genColor = glm::vec3(0.0f, 0.5f, 1.0f);			// color
				m_particleSettings.genLifeMin = 1.5f;								// min lifeTime
				m_particleSettings.genLifeMax = 3.0f;								// max lifeTime
				m_particleSettings.genSize = 1.75f;									// size
				m_particleSettings.nextGenerationTime = 0.02f;						// spawn in 0.02s
				m_particleSettings.numberToGenerate = 30;							// count of particles
			}

		public:
			void Init()
			{
				InitSettings();

				m_particleTexture = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/particle.png", true);
				m_particleTexture->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

				m_particleSystem->SetUpdateShaderPaths(std::vector<std::string> {"./TestScene/Assets/Shaders/Particles/ParticlesUpdate.vert.hlsl", "./TestScene/Assets/Shaders/Particles/ParticlesUpdate.geom.hlsl"}, "./TestScene/Assets/Shaders/Binary/ParticlesUpdateShader.bin");
				m_particleSystem->SetRenderShaderPaths(std::vector<std::string> {"./TestScene/Assets/Shaders/Particles/ParticlesRender.vert.hlsl", "./TestScene/Assets/Shaders/Particles/ParticlesRender.geom.hlsl", "./TestScene/Assets/Shaders/Particles/ParticlesRender.frag.hlsl"}, "./TestScene/Assets/Shaders/Binary/ParticlesRenderShader.bin");
				m_particleSystem->Init();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;
				ss << "Number of particles: " << m_particleSystem->GetNumberOfParticles() << std::endl;
				ss << "Particle Position: [" << m_particleSettings.genPosition.x << ", " << m_particleSettings.genPosition.y << ", " << m_particleSettings.genPosition.z << "]" << std::endl;
				ss << "Particle VelocityMin: [" << m_particleSettings.genVelocityMin.x << ", " << m_particleSettings.genVelocityMin.y << ", " << m_particleSettings.genVelocityMin.z << "]" << std::endl;
				ss << "Particle VelocityMax: [" << m_particleSettings.genVelocityMax.x << ", " << m_particleSettings.genVelocityMax.y << ", " << m_particleSettings.genVelocityMax.z << "]" << std::endl;
				ss << "Particle Gravity: [" << m_particleSettings.genGravity.x << ", " << m_particleSettings.genGravity.y << ", " << m_particleSettings.genGravity.z << "]" << std::endl;
				ss << "Particle Color: [" << m_particleSettings.genColor.x << ", " << m_particleSettings.genColor.y << ", " << m_particleSettings.genColor.z << "]" << std::endl;
				ss << "Particle Size: " << m_particleSettings.genSize << std::endl;
				ss << "---------------------------------------" << std::endl;
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_1)) m_particleSettings.genPosition += glm::vec3(POSITION_STEP * deltaTime, POSITION_STEP * deltaTime, POSITION_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_2)) m_particleSettings.genPosition -= glm::vec3(POSITION_STEP * deltaTime, POSITION_STEP * deltaTime, POSITION_STEP * deltaTime);

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_3)) m_particleSettings.genVelocityMin += glm::vec3(VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_4)) m_particleSettings.genVelocityMin -= glm::vec3(VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime);

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_3)) m_particleSettings.genVelocityMax += glm::vec3(VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_4)) m_particleSettings.genVelocityMax -= glm::vec3(VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime, VELOCITY_STEP * deltaTime);

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_5)) m_particleSettings.genGravity.y += GRAVITY_STEP * deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_6)) m_particleSettings.genGravity.y -= GRAVITY_STEP * deltaTime;

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_7)) m_particleSettings.genColor.y += COLOR_STEP * deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_8)) m_particleSettings.genColor.y -= COLOR_STEP * deltaTime;

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_9)) m_particleSettings.genSize += SIZE_STEP * deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_0)) m_particleSettings.genSize -= SIZE_STEP * deltaTime;
			}

			void PreRender()
			{
			}

			void PostRender()
			{
				//m_particleSystem->RenderNormals();
			}

			void Render()
			{
				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();

				m_particleTexture->Bind();
				m_particleSystem->UpdateSettings(m_particleSettings);
				m_particleSystem->UpdateProjectionMatrix(m_perspectiveProjectionMatrix);
				m_particleSystem->UpdateViewer(camera->GetCamera()->GetEye(), camera->GetCamera()->GetView(), camera->GetCamera()->GetUp());
				m_particleSystem->Update(m_deltaTime);
				m_particleSystem->Render();
			}

			void ShutDown()
			{
				m_particleTexture->Delete();
			}

			const ParticleSystemTransformFeedbackSettings& GetCurrentSettings() const
			{
				return m_particleSettings;
			}

			unsigned int GetCountOfParticles() const
			{
				return m_particleSystem->GetNumberOfParticles();
			}

		public:
			void OnKeyPressedHandler(const OnKeyPress& press)
			{
			}

			void OnKeyReleasedHandler(const OnKeyRelease& release)
			{
			}
		};
	}
}

#endif