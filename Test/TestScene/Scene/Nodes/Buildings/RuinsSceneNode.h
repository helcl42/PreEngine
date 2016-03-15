#ifndef RUINS_SCENE_NODE_H
#define RUINS_SCENE_NODE_H

#include "../BaseSceneNode.h"
#include "RuinsPartSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;

		template <class RootType>
		class RuinsSceneNode : public BaseSceneNode<RuinsSceneNode<RootType>, RootType>
		{
		private:
			IShaderProgram* m_mainProgram;

			IShaderProgram* m_normalsProgram;

			IModel* m_ruinModel;

			IAssimpModelFactory* m_modelFactory;

			RuinsPartSceneNode<RootType>* m_parts[4];

		public:
			RuinsSceneNode(RootType* root)
				: BaseSceneNode<RuinsSceneNode<RootType>, RootType>(root)
			{
				m_modelFactory = new AssimpModelFactory();

				for (unsigned int i = 0; i < 4; i++)
				{
					RuinsPartSceneNode<RootType>* part = new RuinsPartSceneNode<RootType>(m_root);
					m_parts[i] = part;
					AddChild(part);
				}
			}

			virtual ~RuinsSceneNode()
			{
				for (std::vector<ISceneNode*>::iterator ii = m_children.begin(); ii != m_children.end(); ++ii)
				{
					SAFE_DELETE(*ii);
				}

				SAFE_DELETE(m_mainProgram);
				SAFE_DELETE(m_normalsProgram);
				SAFE_DELETE(m_modelFactory);
				SAFE_DELETE(m_ruinModel);
			}

		public:
			void Init()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/AssimpShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Assimp/Main.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Assimp/Main.frag.hlsl");
				m_mainProgram = m_programBuilder->Build(true, false);

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/NormalsShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::GEOMETRY_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.geom.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.frag.hlsl");
				m_normalsProgram = m_programBuilder->Build();

				m_ruinModel = m_modelFactory->CreateModel("./TestScene/Assets/Models/ColRuins/Ruins.obj", "./TestScene/Assets/Models/ColRuins/DiffuseMap.tga", "./TestScene/Assets/Models/ColRuins/NormalMap.tga");

				m_mainProgram->Use();
				m_mainProgram->SetUniform("gSampler", 0);
				m_mainProgram->SetUniform("gNormalMap", 1);

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(2);
				shadows->GetShadows()->SetUniformData(m_mainProgram, "shadows");
				m_mainProgram->Validate();

				glm::vec3 positions[] = 
				{
					glm::vec3(-150.0f, 0.1f, -150.0f),
					glm::vec3(150.0f, 0.1f, -150.0f),
					glm::vec3(150.0f, 0.1f, 150.0f),
					glm::vec3(-150.0f, 0.1f, 150.0f)
				};

				float rotationsY[] = { 0.0f, -90.0f, -180.0f, -270.0f };

				for (unsigned int i = 0; i < m_children.size(); i++)
				{
					m_parts[i]->SetMainProgram(m_mainProgram);
					m_parts[i]->SetNormalsProgram(m_normalsProgram);
					m_parts[i]->SetModel(m_ruinModel);
					m_parts[i]->SetPosition(positions[i]);
					m_parts[i]->SetYRotation(rotationsY[i]);
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

				m_ruinModel->Delete();
				SAFE_DELETE(m_ruinModel);

				m_normalsProgram->DeleteShaders();
				m_normalsProgram->Delete();
				SAFE_DELETE(m_normalsProgram);

				m_mainProgram->DeleteShaders();
				m_mainProgram->Delete();
				SAFE_DELETE(m_mainProgram);
			}
		};
	}
}

#endif