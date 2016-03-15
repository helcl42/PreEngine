#ifndef ARMY_MEN_SCENE_NODE_H
#define ARMY_MEN_SCENE_NODE_H

#include <PreEngine/Render/Models/MD2/MD2ModelFactory.h>
#include "../BaseSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models::MD2;

		template <class RootType>
		class ArmyMenSceneNode : public BaseSceneNode<ArmyMenSceneNode<RootType>, RootType>
		{
		private:
			IAnimatedModel* m_solderModel;

			IShaderProgram* m_animationProgram;

			AnimationState m_animationState;

			AnimationType m_animationType;

			float m_currentTimeOffset;

			glm::vec3 m_position;

			std::string m_modelFilePath;


		public:
			ArmyMenSceneNode(RootType* root)
				: BaseSceneNode<ArmyMenSceneNode<RootType>, RootType>(root)
			{
			}

			virtual ~ArmyMenSceneNode()
			{
			}

		private:
			void RenderCommon()
			{
				m_model = glm::translate(glm::mat4(1.0f), m_position);
				m_model = glm::rotate(m_model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				m_model = glm::scale(m_model, glm::vec3(0.35f, 0.35f, 0.35f));

				SetMatrices(m_animationProgram);

				m_solderModel->SetShaderProgram(m_animationProgram);
				m_solderModel->UpdateAnimation(&m_animationState, m_deltaTime * 0.8f);
				m_solderModel->Render(&m_animationState);
			}

		public:
			void Init()
			{
				m_animationState = m_solderModel->StartAnimation(m_animationType);
				m_animationState.curr_time = m_currentTimeOffset;
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
			}

			void PreRender()
			{
				m_animationProgram->Use();
				m_animationProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "RecordDepth");

				RenderCommon();
			}

			void Render()
			{
				m_animationProgram->Use();
				m_animationProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "ShadeWithShadow");
				m_animationProgram->SetUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				m_animationProgram->SetUniform("gSampler", 0);

				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();
				m_animationProgram->SetUniform("eyePosition", camera->GetCamera()->GetEye());

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(1);
				shadows->GetShadows()->SetUniformData(m_animationProgram, "shadows");
				shadows->GetShadows()->BindFrameBufferTexture();

				FindSingleByType<SunSceneNode<RootType>>()->GetSunLight().SetUniformData(m_animationProgram, "sunLight");

				m_shinyMaterial.SetUniformData(m_animationProgram, "activeMaterial");

				RenderCommon();
			}

			void PostRender()
			{
			}

			void ShutDown()
			{
			}

			void SetModel(IAnimatedModel* model)
			{
				m_solderModel = model;
			}

			void SetProgram(IShaderProgram* program)
			{
				m_animationProgram = program;
			}

			void SetPosition(glm::vec3 position)
			{
				m_position = position;
			}

			void SetCurrentTimeOffset(float offset)
			{
				m_currentTimeOffset = offset;
			}

			void SetAnimationType(AnimationType type)
			{
				m_animationType = type;
			}
		};
	}
}

#endif