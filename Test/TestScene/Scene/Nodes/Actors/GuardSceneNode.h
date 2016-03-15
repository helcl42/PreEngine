#ifndef GUARD_SCENE_NODE_H
#define GUARD_SCENE_NODE_H

#include <PreEngine/Render/Models/MD5/MD5ModelFactory.h>

#include "../BaseSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models::MD5;

		template <class RootType>
		class GuardSceneNode : public BaseSceneNode<GuardSceneNode<RootType>, RootType>
		{
		private:
			MD5Model* m_guardModel;

			IShaderProgram* m_mainProgram;

			IMD5ModelFactory* m_md5ModelFactory;

			std::string m_modelFilePath;


		public:
			GuardSceneNode(RootType* root, std::string modelPath)
				: BaseSceneNode<GuardSceneNode<RootType>, RootType>(root), m_modelFilePath(modelPath)
			{
				m_md5ModelFactory = new MD5ModelFactory();
			}

			virtual ~GuardSceneNode()
			{
				SAFE_DELETE(m_mainProgram);
				SAFE_DELETE(m_md5ModelFactory);
			}

		private:
			void RenderCommon()
			{
				m_model = glm::translate(glm::mat4(1.0), glm::vec3(-100.0f, 37.0f, 4.0f));
				m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
				m_model = glm::scale(m_model, glm::vec3(0.25, 0.25, 0.25));

				SetMatrices(m_mainProgram);

				const std::vector<glm::mat4>& transforms = m_guardModel->GetBoneTransforms();
				for (unsigned int i = 0; i < transforms.size(); i++)
				{
					std::stringstream ss;
					ss << "gBones[" << i << "]";
					m_mainProgram->SetUniform(ss.str(), transforms[i]);
				}

				m_guardModel->Render();
			}

		public:
			void Init()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/MD5AnimationShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD5.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD5.frag.hlsl");
				m_mainProgram = m_programBuilder->Build(true, false);

				m_mainProgram->Use();
				m_mainProgram->SetUniform("gSampler", 0);

				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();
				m_mainProgram->SetUniform("eyePosition", camera->GetCamera()->GetEye());

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(1);
				shadows->GetShadows()->SetUniformData(m_mainProgram, "shadows");
				m_mainProgram->Validate();

				m_guardModel = m_md5ModelFactory->CreateModel(m_modelFilePath);
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				m_guardModel->Update(deltaTime);
			}

			void PreRender()
			{
				m_mainProgram->Use();
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "RecordDepth");

				RenderCommon();
			}

			void Render()
			{
				m_mainProgram->Use();
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "ShadeWithShadow");
				m_mainProgram->SetUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				m_mainProgram->SetUniform("gSampler", 0);

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(1);
				shadows->GetShadows()->SetUniformData(m_mainProgram, "shadows");
				shadows->GetShadows()->BindFrameBufferTexture();

				FindSingleByType<SunSceneNode<RootType>>()->GetSunLight().SetUniformData(m_mainProgram, "sunLight");

				m_shinyMaterial.SetUniformData(m_mainProgram, "activeMaterial");

				RenderCommon();
			}

			void PostRender()
			{
			}

			void ShutDown()
			{
				m_guardModel->Delete();
				SAFE_DELETE(m_guardModel);

				m_mainProgram->DeleteShaders();
				m_mainProgram->Delete();
				SAFE_DELETE(m_mainProgram);
			}
		};
	}
}

#endif