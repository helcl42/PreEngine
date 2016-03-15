#ifndef SKYBOX_SCENE_NODE_H
#define SKYBOX_SCENE_NODE_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/SkyBoxes/SkyBoxFactory.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::SkyBoxes;

		template <class RootType>
		class SkyboxSceneNode : public BaseSceneNode<SkyboxSceneNode<RootType>, RootType>
		{
		private:
			ISkyBox* m_skyBox;

			ISkyBoxFactory* m_skyBoxFactory;

			IShaderProgram* m_skyBoxProgram;

		public:
			SkyboxSceneNode(RootType* root)
				: BaseSceneNode<SkyboxSceneNode<RootType>, RootType>(root)
			{
				m_skyBoxFactory = new SkyBoxFactory();
			}

			virtual ~SkyboxSceneNode()
			{
				SAFE_DELETE(m_skyBoxFactory);
				SAFE_DELETE(m_skyBox);
				SAFE_DELETE(m_skyBoxProgram);
			}

		public:
			void Init()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/SkyBoxShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Skybox/Skybox.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Skybox/Skybox.frag.hlsl");
				m_skyBoxProgram = m_programBuilder->Build();

				m_skyBox = m_skyBoxFactory->CreateSkyBox("./TestScene/Assets/Skyboxes/clouds/", "clouds_front.png", "clouds_back.png", "clouds_right.png", "clouds_left.png", "clouds_top.png", "clouds_top.png");
			}

			void Update(float deltaTime)
			{
			}

			void PreRender()
			{
			}

			void PostRender()
			{
			}

			void Render()
			{
				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();

				m_model = glm::translate(glm::mat4(1.0), camera->GetCamera()->GetEye());

				m_skyBoxProgram->Use();

				m_skyBoxProgram->SetUniform("color", glm::vec4(0.8f, 0.75f, 0.75f, 1.0f));
				m_skyBoxProgram->SetUniform("gSampler", 0);

				m_skyBoxProgram->SetUniform("matrices.projectionMatrix", m_perspectiveProjectionMatrix);
				m_skyBoxProgram->SetUniform("matrices.viewMatrix", camera->GetCamera()->LookAt());
				m_skyBoxProgram->SetUniform("matrices.modelMatrix", m_model);
				m_skyBoxProgram->SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(m_model)));
				m_skyBox->Render();
			}

			void ShutDown()
			{
				m_skyBox->Delete();

				m_skyBoxProgram->Delete();
				m_skyBoxProgram->DeleteShaders();
				SAFE_DELETE(m_skyBoxProgram);
			}
		};
	}
}

#endif