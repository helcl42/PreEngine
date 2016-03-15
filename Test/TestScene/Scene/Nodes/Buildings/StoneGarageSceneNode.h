#ifndef STONE_GARAGE_SCENE_OBJECT_H
#define STONE_GARAGE_SCENE_OBJECT_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/Models/Assimp/AssimpModelFactory.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models;
		using namespace PreEngine::Render::Models::Assimp;

		template <class RootType>
		class StoneGarageSceneNode : public BaseSceneNode<StoneGarageSceneNode<RootType>, RootType>
		{
		private:
			IShaderProgram* m_mainProgram;

			IShaderProgram* m_normalsProgram;

			IModel* m_garageModel;

			IAssimpModelFactory* m_modelFactory;


		public:
			StoneGarageSceneNode(RootType* root)
				: BaseSceneNode<StoneGarageSceneNode<RootType>, RootType>(root)
			{
				m_modelFactory = new AssimpModelFactory();
			}

			virtual ~StoneGarageSceneNode()
			{
				SAFE_DELETE(m_mainProgram);
				SAFE_DELETE(m_normalsProgram);
				SAFE_DELETE(m_modelFactory);
				SAFE_DELETE(m_garageModel);
			}

		private:
			void RenderCommon(IShaderProgram* program, GLenum how)
			{
				m_model = glm::translate(glm::mat4(1.0), glm::vec3(110.0f, 39.0f, -30.0));
				m_model = glm::scale(m_model, glm::vec3(3.0f, 2.0f, 2.5f));

				SetMatrices(program);

				m_garageModel->Render(how);
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

				m_garageModel = m_modelFactory->CreateModel("./TestScene/Assets/Models/StoneWall/stone_wall.obj", "./TestScene/Assets/Models/StoneWall/stone_wall.bmp", "./TestScene/Assets/Models/StoneWall/stone_wall_normal_map.bmp");

				m_mainProgram->Use();
				m_mainProgram->SetUniform("gSampler", 0);
				m_mainProgram->SetUniform("gNormalMap", 1);

				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();
				m_mainProgram->SetUniform("eyePosition", camera->GetCamera()->GetEye());

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(2);
				shadows->GetShadows()->SetUniformData(m_mainProgram, "shadows");
				m_mainProgram->Validate();

				m_shinyMaterial = Material(1.0f, 32.0f);
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
				m_garageModel->Delete();

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