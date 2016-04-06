#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/Models/MD2/MD2ModelFactory.h>
#include <PreEngine/Render/Picking/RayCastingPicking.h>
#include <PreEngine/Render/Models/Primitives/Line.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Picking;
		using namespace PreEngine::Render::Models::MD2;
		using namespace PreEngine::Render::Models::Primitives;
		using namespace PreEngine::Inputs;

		template <class RootType>
		class MainActorSceneNode : public BaseSceneNode<MainActorSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			const unsigned int COUNT_OF_MODELS = 4;

			IShaderProgram* m_boundingBoxesProgram;

			IShaderProgram* m_animationProgram;

			IMD2ModelFactory* m_md2ModelFactory;

			IAnimatedModel** m_models;

			std::string* m_modelNames;

			glm::vec3 m_modelPosition;

			float m_modelRotation;

			int m_currentModel;

			AnimationState m_actualAnimationState;

			AnimationType m_currentAnimation;

			IInputFacade* m_inputFacade;
			

			IModel* m_boundingSphere;

			RayCastingPicking m_rayCastingPicking;

		public:
			MainActorSceneNode(RootType* root)
				: BaseSceneNode<MainActorSceneNode<RootType>, RootType>(root)
			{
				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);

				m_models = new IAnimatedModel*[COUNT_OF_MODELS];
				m_modelNames = new std::string[COUNT_OF_MODELS] { "Dr. Freak", "Blade", "Samourai", "HoboGoblin" };

				m_md2ModelFactory = new MD2ModelFactory();
				m_boundingSphere = new Sphere(1.0f, 32, 32);
			}

			virtual ~MainActorSceneNode()
			{
				SAFE_DELETE(m_boundingSphere);
				SAFE_DELETE(m_boundingBoxesProgram);
				SAFE_DELETE(m_animationProgram);
				SAFE_DELETE(m_md2ModelFactory);

				SAFE_DELETE_ARRAY(m_modelNames);
				for (unsigned int i = 0; i < COUNT_OF_MODELS; i++)
				{
					SAFE_DELETE(m_models[i]);
				}
				SAFE_DELETE_ARRAY(m_models);

				SAFE_DELETE(m_inputFacade);
			}

		private:
			void RenderCommon()
			{
				m_model = glm::translate(glm::mat4(1.0), glm::vec3(m_modelPosition));
				m_model = glm::rotate(m_model, glm::radians(m_modelRotation), glm::vec3(0, 1, 0));
				m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
				m_model = glm::scale(m_model, glm::vec3(0.35f, 0.35f, 0.35f));

				SetMatrices(m_animationProgram);

				m_models[m_currentModel]->SetShaderProgram(m_animationProgram);
				m_models[m_currentModel]->UpdateAnimation(&m_actualAnimationState, m_deltaTime * 0.8f);
				m_models[m_currentModel]->Render(&m_actualAnimationState);
			}

			void RenderBoundingSpheres()
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				const float BOUNDING_SPHERE_RADIUS = 4.5f;

				m_boundingBoxesProgram->Use();

				glm::mat4 lookAt = FindSingleByType<CameraSceneNode<RootType>>()->GetCamera()->LookAt();
				Ray ray = m_rayCastingPicking.Get3DRayAtMousePosition(lookAt);

				// sphere 1
				glm::vec3 boundingSpherePosition1 = glm::vec3(m_modelPosition);
				boundingSpherePosition1.y -= 5.0;

				if (m_rayCastingPicking.RaySphereCollision(ray, boundingSpherePosition1, BOUNDING_SPHERE_RADIUS)) m_boundingBoxesProgram->SetUniform("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				else m_boundingBoxesProgram->SetUniform("color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

				m_model = glm::translate(glm::mat4(1.0), boundingSpherePosition1);
				m_model = glm::scale(m_model, glm::vec3(BOUNDING_SPHERE_RADIUS, BOUNDING_SPHERE_RADIUS, BOUNDING_SPHERE_RADIUS));
				SetMatrices(m_boundingBoxesProgram);
				m_boundingSphere->Render();

				// sphere 2
				glm::vec3 boundingSpherePosition2 = glm::vec3(m_modelPosition);
				boundingSpherePosition2.y += 2.0;

				if (m_rayCastingPicking.RaySphereCollision(ray, boundingSpherePosition2, BOUNDING_SPHERE_RADIUS)) m_boundingBoxesProgram->SetUniform("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				else m_boundingBoxesProgram->SetUniform("color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

				m_model = glm::translate(glm::mat4(1.0), boundingSpherePosition2);
				m_model = glm::scale(m_model, glm::vec3(BOUNDING_SPHERE_RADIUS, BOUNDING_SPHERE_RADIUS, BOUNDING_SPHERE_RADIUS));
				SetMatrices(m_boundingBoxesProgram);
				m_boundingSphere->Render();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

		public:
			void Init()
			{
				m_modelPosition = glm::vec3(67.0, 47.0, -7.0);
				m_modelRotation = 0.0f;
				m_currentModel = 0;
				m_currentAnimation = AnimationType::STAND;

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/BoundingBoxesShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/BoundingBoxes/BoundingBoxes.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/BoundingBoxes/BoundingBoxes.frag.hlsl");
				m_boundingBoxesProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/MD2AnimationShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD2.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Animation/AnimationMD2.frag.hlsl");
				m_animationProgram = m_programBuilder->Build(true, false);

				m_models[0] = m_md2ModelFactory->CreateModel("./TestScene/Assets/Models/drfreak/drfreak.md2");
				m_models[1] = m_md2ModelFactory->CreateModel("./TestScene/Assets/Models/blade/Blade.md2");
				m_models[2] = m_md2ModelFactory->CreateModel("./TestScene/Assets/Models/samourai/Samourai.md2");
				m_models[3] = m_md2ModelFactory->CreateModel("./TestScene/Assets/Models/HoboGoblin/Model.md2");
				m_actualAnimationState = m_models[m_currentModel]->StartAnimation(AnimationType::STAND);

				m_animationProgram->Use();
				m_animationProgram->SetUniform("gSampler", 0);

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(1);
				shadows->GetShadows()->SetUniformData(m_animationProgram, "shadows");

				m_animationProgram->Validate();

				m_boundingSphere->Init();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;
				ss << "Current Model: " << GetCurrentModelName() << std::endl;
				ss << "Current Model Animation: " << GetAnimationTypeName(GetCurrentAnimationType()) << std::endl;
				ss << "---------------------------------------" << std::endl;
				return std::string(ss.str());
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

				RenderBoundingSpheres();
			}

			void PostRender()
			{
			}

			void ShutDown()
			{
				for (unsigned int i = 0; i < COUNT_OF_MODELS; i++)
				{
					m_models[i]->ShutDown();
				}

				m_boundingBoxesProgram->Delete();
				m_boundingBoxesProgram->DeleteShaders();
				SAFE_DELETE(m_boundingBoxesProgram);

				m_animationProgram->Delete();
				m_animationProgram->DeleteShaders();
				SAFE_DELETE(m_animationProgram);

				m_boundingSphere->Delete();
			}

			std::string GetCurrentModelName() const
			{
				return m_modelNames[m_currentModel];
			}

			AnimationType GetCurrentAnimationType() const
			{
				return m_currentAnimation;
			}

		public:
			void OnKeyPressedHandler(const OnKeyPress& press)
			{
				if (press.key == GLFW_KEY_Z) m_currentModel = (m_currentModel + 1) % COUNT_OF_MODELS;

				if (press.key == GLFW_KEY_C)
				{
					m_currentAnimation = AnimationType((int(m_currentAnimation) + int(MAX_ANIMATIONS - 1) - 1) % int(MAX_ANIMATIONS - 1));
					m_actualAnimationState = m_models[m_currentModel]->StartAnimation(m_currentAnimation);
				}

				if (press.key == GLFW_KEY_V)
				{
					m_currentAnimation = AnimationType((int(m_currentAnimation) + 1) % int(MAX_ANIMATIONS - 1));
					m_actualAnimationState = m_models[m_currentModel]->StartAnimation(m_currentAnimation);
				}
			}

			void OnKeyReleasedHandler(const OnKeyRelease& release)
			{
			}
		};
	}
}
