#ifndef SUN_SCENE_NODE_H
#define SUN_SCENE_NODE_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/Lightning/DirectionalLight.h>
#include <PreEngine/Render/Models/Primitives/Sphere.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models;
		using namespace PreEngine::Render::Models::Primitives;
		using namespace PreEngine::Render::Lightning;
		using namespace PreEngine::Inputs;

		template <class RootType>
		class SunSceneNode : public BaseSceneNode<SunSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			const float SUN_OFFSET_STEP = 30.0f;

			DirectionalLight m_sunLight;

			IModel* m_sphere;

			ITexture* m_sunTexture;

			ITextureFactory* m_textureFactory;

			IShaderProgram* m_mainProgram;

			IInputFacade* m_inputFacade;

		public:
			SunSceneNode(RootType* root)
				: BaseSceneNode<SunSceneNode<RootType>, RootType>(root)
			{
				m_sunLight = DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(208.0, 264.0, 194.0), 0.5f);

				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);

				m_textureFactory = new TextureFactory();
			}

			virtual ~SunSceneNode()
			{
				SAFE_DELETE(m_mainProgram);

				SAFE_DELETE(m_sunTexture);
				SAFE_DELETE(m_sphere);
				SAFE_DELETE(m_textureFactory);
				SAFE_DELETE(m_inputFacade);
			}

		public:
			void Init()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/SunShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Sun/Main.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Sun/Main.frag.hlsl");
				m_mainProgram = m_programBuilder->Build(true, false);

				m_sunTexture = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/sand.png", true);
				m_sunTexture->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

				m_sphere = new Sphere(1.0f, 50, 50);
				m_sphere->Init();

				m_mainProgram->Use();
				m_mainProgram->SetUniform("gSampler", 0);
				m_mainProgram->Validate();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;
				ss << "Sun Position: [" << m_sunLight.GetDirection().x << ", " << m_sunLight.GetDirection().y << ", " << m_sunLight.GetDirection().z << "]" << std::endl;
				ss << "---------------------------------------" << std::endl;
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_O)) m_sunLight.UpdateDirectionX(SUN_OFFSET_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_P)) m_sunLight.UpdateDirectionX(-SUN_OFFSET_STEP * deltaTime);

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_L)) m_sunLight.UpdateDirectionY(SUN_OFFSET_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_K)) m_sunLight.UpdateDirectionY(-SUN_OFFSET_STEP * deltaTime);

				if (m_inputFacade->IsKeyPressed(GLFW_KEY_M)) m_sunLight.UpdateDirectionZ(SUN_OFFSET_STEP * deltaTime);
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_N)) m_sunLight.UpdateDirectionZ(-SUN_OFFSET_STEP * deltaTime);
			}

			void PreRender()
			{
			}

			void Render()
			{
				m_mainProgram->Use();
				m_mainProgram->SetUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "ShadeWithShadow");

				m_model = glm::mat4(1.0f);
				m_model = glm::translate(m_model, m_sunLight.GetDirection());
				m_model = glm::scale(m_model, glm::vec3(5.0, 5.0, 5.0));
				m_sunTexture->Bind();
				SetMatrices(m_mainProgram);
				m_sphere->Render();
			}

			void PostRender()
			{
			}

			void ShutDown()
			{
				m_mainProgram->Delete();
				m_mainProgram->DeleteShaders();
				SAFE_DELETE(m_mainProgram);

				m_sphere->Delete();
				m_sunTexture->Delete();
			}

			DirectionalLight GetSunLight() const
			{
				return m_sunLight;
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