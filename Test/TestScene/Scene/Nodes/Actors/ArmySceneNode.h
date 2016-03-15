#ifndef ARMY_SCENE_NODE_H
#define ARMY_SCENE_NODE_H

#include "ArmyMenSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models::MD2;

		template <class RootType>
		class ArmySceneNode : public BaseSceneNode<ArmySceneNode<RootType>, RootType>
		{
		private:
			std::string m_modelFilePath;

			IShaderProgram* m_animationProgram;

			IMD2ModelFactory* m_md2ModelFactory;

			IAnimatedModel* m_solderModel;

			ArmyMenSceneNode<RootType>* m_men[15];

		public:
			ArmySceneNode(RootType* root, std::string modelFilePath)
				: BaseSceneNode<ArmySceneNode<RootType>, RootType>(root), m_modelFilePath(modelFilePath)
			{
				m_md2ModelFactory = new MD2ModelFactory();
				
				for (int i = 0; i < 15; i++)
				{
					ArmyMenSceneNode<RootType>* man = new ArmyMenSceneNode<RootType>(m_root);
					m_men[i] = man;
					AddChild(man);
				}
			}

			virtual ~ArmySceneNode()
			{
				for (std::vector<ISceneNode*>::iterator ii = m_children.begin(); ii != m_children.end(); ++ii)
				{
					SAFE_DELETE(*ii);
				}

				SAFE_DELETE(m_solderModel);
				SAFE_DELETE(m_animationProgram);
				SAFE_DELETE(m_md2ModelFactory);
			}

		public:
			void Init()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/MD2AnimationShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD2.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD2.frag.hlsl");
				m_animationProgram = m_programBuilder->Build(true, false);

				m_animationProgram->Use();
				m_animationProgram->SetUniform("gSampler", 0);
				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(1);
				shadows->GetShadows()->SetUniformData(m_animationProgram, "shadows");
				m_animationProgram->Validate();

				m_solderModel = m_md2ModelFactory->CreateModel(m_modelFilePath);

				TerrainSceneNode<RootType>* terrain = FindSingleByType<TerrainSceneNode<RootType>>();

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						int index = i * 5 + j;
						m_men[index]->SetProgram(m_animationProgram);
						m_men[index]->SetModel(m_solderModel);
						m_men[index]->SetAnimationType(rand() % 2 ? AnimationType::ATTACK : rand() % 2 ? AnimationType::STAND : AnimationType::SALUTE);
						m_men[index]->SetCurrentTimeOffset(-(i + j) * 0.15f);
						m_men[index]->SetPosition(glm::vec3(80.0f + j * 15.0f, terrain->GetHeightFromRealVector(glm::vec3(0.0)) + 35.0f, -110.0f + i * 15.0f));
					}
				}

				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->Init();
				}
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->Update(deltaTime);
				}
			}

			void PreRender()
			{
				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->PreRender();
				}
			}

			void Render()
			{
				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->Render();
				}
			}

			void PostRender()
			{
				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->PostRender();
				}
			}

			void ShutDown()
			{
				for (std::vector<ISceneNode*>::const_iterator ci = m_children.cbegin(); ci != m_children.cend(); ++ci)
				{
					(*ci)->ShutDown();
				}

				m_solderModel->ShutDown();
				SAFE_DELETE(m_solderModel);

				m_animationProgram->Delete();
				m_animationProgram->DeleteShaders();
				SAFE_DELETE(m_animationProgram);
			}
		};
	}
}

#endif