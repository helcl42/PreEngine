#ifndef RUNINS_PART_SCENE_NODE_H
#define RUNINS_PART_SCENE_NODE_H

#include "../BaseSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;

		template <class RootType>
		class RuinsPartSceneNode : public BaseSceneNode<RuinsPartSceneNode<RootType>, RootType>
		{
		private:
			const float RUINS_SCALE_FACTOR = 0.85f;


			IShaderProgram* m_mainProgram;

			IShaderProgram* m_normalsProgram;

			IModel* m_ruinModel;

			glm::vec3 m_position;

			float m_yRotation;


		public:
			RuinsPartSceneNode(RootType* root)
				: BaseSceneNode<RuinsPartSceneNode<RootType>, RootType>(root)
			{
			}

			virtual ~RuinsPartSceneNode()
			{
			}

		private:
			void RenderCommon(IShaderProgram* program, GLenum how)
			{
				m_model = glm::translate(glm::mat4(1.0), m_position);
				m_model = glm::rotate(m_model, glm::radians(m_yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
				m_model = glm::scale(m_model, glm::vec3(RUINS_SCALE_FACTOR, RUINS_SCALE_FACTOR, RUINS_SCALE_FACTOR));
				SetMatrices(program);
				m_ruinModel->Render(how);
			}

		public:
			void Init()
			{
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
			}

			void PreRender()
			{
				m_mainProgram->Use();
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "RecordDepth");

				RenderCommon(m_mainProgram, GL_TRIANGLES);
			}

			void Render()
			{
				m_mainProgram->Use();
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "ShadeWithShadow");

				m_mainProgram->SetUniform("bumpMapEnabled", m_useBumpMaps);
				m_mainProgram->SetUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				m_shinyMaterial.SetUniformData(m_mainProgram, "activeMaterial");

				FindSingleByType<SunSceneNode<RootType>>()->GetSunLight().SetUniformData(m_mainProgram, "sunLight");

				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();
				m_mainProgram->SetUniform("eyePosition", camera->GetCamera()->GetEye());

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(2);
				shadows->GetShadows()->SetUniformData(m_mainProgram, "shadows");
				shadows->GetShadows()->BindFrameBufferTexture();

				RenderCommon(m_mainProgram, GL_TRIANGLES);
			}

			void PostRender()
			{
				m_normalsProgram->Use();
				m_normalsProgram->SetUniform("normalLength", m_normalLength);
				RenderCommon(m_normalsProgram, GL_POINTS);
			}

			void ShutDown()
			{
			}

			void SetMainProgram(IShaderProgram* mainProgram)
			{
				m_mainProgram = mainProgram;
			}

			void SetNormalsProgram(IShaderProgram* normalsProgram)
			{
				m_normalsProgram = normalsProgram;
			}

			void SetModel(IModel* model)
			{
				m_ruinModel = model;
			}

			void SetYRotation(float rotation) 
			{
				m_yRotation = rotation;
			}

			float GetYRotation() const
			{
				return m_rotation;
			}

			void SetPosition(glm::vec3 position)
			{
				m_position = position;
			}

			glm::vec3 GetPosition() const
			{
				return m_position;
			}
		};
	}
}

#endif