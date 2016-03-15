#ifndef POST_PROCESS_SCENE_NODE_H
#define POST_PROCESS_SCENE_NODE_H

#include <PreEngine/Render/Models/Static/Quad.h>

#include "../BaseSceneNode.h"
#include "MotionBlurSettings.h"
#include "HDRSceneNode.h"
#include "LensFlareSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Models;
		using namespace PreEngine::Render::Models::Static;
		using namespace PreEngine::Render::Lightning;
		using namespace PreEngine::Inputs;

		template <class RootType>
		class PostProcessSceneNode : public BaseSceneNode<PostProcessSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			IFrameBuffer* m_originFrameBuffer;

			IShaderProgram* m_finalCompositorProgram;

			IInputFacade* m_inputFacade;

			Quad *m_fullScreenQuad;

			MotionBlurSettings m_motionBlurSettings;

			bool m_isEnabled = true;

			glm::mat4 m_previousViewProjectionMatrix;

			HDRSceneNode<RootType>* m_hdrSceneNode;

			LensFlareSceneNode<RootType>* m_lensFlareSceneNode;

		public:
			PostProcessSceneNode(RootType* root)
				: BaseSceneNode<PostProcessSceneNode<RootType>, RootType>(root)
			{
				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);

				m_hdrSceneNode = new HDRSceneNode<RootType>(m_root);
				m_lensFlareSceneNode = new LensFlareSceneNode<RootType>(m_root);
			}

			virtual ~PostProcessSceneNode()
			{
				SAFE_DELETE(m_lensFlareSceneNode);
				SAFE_DELETE(m_hdrSceneNode);
				SAFE_DELETE(m_finalCompositorProgram);
				SAFE_DELETE(m_inputFacade);
				SAFE_DELETE(m_originFrameBuffer);
				SAFE_DELETE(m_fullScreenQuad);
			}

		public:
			void Init()
			{
				m_fullScreenQuad = new Quad();
				m_fullScreenQuad->Init();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/PostProcessFinalCompositorShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/FinalCompositor.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/FinalCompositor.frag.hlsl");
				m_finalCompositorProgram = m_programBuilder->Build();

				FrameBufferFactory frameBufferFactory;
				m_originFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_RGB32F }, true);
				m_originFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR);

				m_hdrSceneNode->Init();		
				m_hdrSceneNode->SetSourceFrameBuffer(m_originFrameBuffer);

				m_lensFlareSceneNode->Init();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;				
				ss << std::endl << "---------------------------------------" << std::endl;
				ss << "PostProcess: " << (m_isEnabled ? "Enabled" : "Disabled") << std::endl;
				ss << "---------------------------------------" << std::endl;
				ss << m_lensFlareSceneNode->GetInfo();
				ss << "Motion Blur: " << (m_motionBlurSettings.isEnabled ? "ON" : "OFF") << std::endl;
				ss << "Motion Speed Scale: " << m_motionBlurSettings.motionScale << std::endl;
				ss << "Motion Speed Original: " << (1.0f / 60.0f) / m_deltaTime << std::endl;
				ss << "Max Motion Samples: " << m_motionBlurSettings.maxMotionSamples << std::endl;
				ss << "---------------------------------------" << std::endl;
				ss << m_hdrSceneNode->GetInfo();
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;

				const float MOTION_BLUR_OFFSET = 0.01f;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_R)) m_motionBlurSettings.motionScale += MOTION_BLUR_OFFSET * m_deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_T)) m_motionBlurSettings.motionScale -= MOTION_BLUR_OFFSET * m_deltaTime;
			}

			void PreRender()
			{
				if (!m_isEnabled) return;

				m_lensFlareSceneNode->PreRender();

				m_originFrameBuffer->Bind();				
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);

				FrameBuffer::SetCustomDefaultFrameBuffer(m_sceneId, m_originFrameBuffer);

				// HERE SHOULD CONTINUE NORMAL RENDER !!!
			}

			void Render()
			{
				
			}

			void PostRender()
			{
				if (!m_isEnabled) return;

				// NORMAL RENDER SHOULD BE FINISHED BEFORE THIS FUNCTION CALL!!!

				FrameBuffer::SetCustomDefaultFrameBuffer(m_sceneId, NULL);

				glm::mat4 actualViewProjectionMatrix = m_projection * m_view;

				m_hdrSceneNode->PostRender();
				m_lensFlareSceneNode->PostRender();

				//////////////////////////////////////////////////////////////
				/// Final render to quad
				//////////////////////////////////////////////////////////////
				FrameBuffer::BindDefaultFrameBuffer(m_sceneId, m_width, m_height);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_finalCompositorProgram->Use();
				m_finalCompositorProgram->SetUniform("mode", int(m_lensFlareSceneNode->GetMode()));
				m_finalCompositorProgram->SetUniform("showLensSource", m_lensFlareSceneNode->ShouldShowLensSource());
				m_finalCompositorProgram->SetUniform("sourceSampler", 0);
				m_finalCompositorProgram->SetUniform("nonSunSourceSampler", 1);
				m_finalCompositorProgram->SetUniform("lensSampler", 2);
				m_finalCompositorProgram->SetUniform("lensDirtSampler", 3);
				m_finalCompositorProgram->SetUniform("lensStarSampler", 4);
				m_finalCompositorProgram->SetUniform("depthSampler", 5);
				m_finalCompositorProgram->SetUniform("lensStarMatrix", m_lensFlareSceneNode->GetStarRotationMatrix());

				m_finalCompositorProgram->SetUniform("previousViewProjectionMatrix", m_previousViewProjectionMatrix);
				m_finalCompositorProgram->SetUniform("inverseViewProjectionMatrix", glm::inverse(actualViewProjectionMatrix));
				m_finalCompositorProgram->SetUniform("motionBlurEnabled", m_motionBlurSettings.isEnabled);
				m_finalCompositorProgram->SetUniform("motionScale", (1.0f / 60.0f) / m_deltaTime);
				m_finalCompositorProgram->SetUniform("maxMotionBlurSamples", m_motionBlurSettings.maxMotionSamples);
				
				SetMatrices(m_finalCompositorProgram);
				
				m_lensFlareSceneNode->GetLensOriginFrameBuffer()->BindFrameBufferTexture(0, 0, true);
				m_hdrSceneNode->GetResultFrameBuffer()->BindFrameBufferTexture(1, 1, true);
				m_originFrameBuffer->BindFrameBufferTexture(0, 5, true);
				m_lensFlareSceneNode->GetResultFrameBuffer()->BindFrameBufferTexture(0, 2, true);
				m_lensFlareSceneNode->GetLensDirtTexture()->Bind(3);
				m_lensFlareSceneNode->GetLensStarTexture()->Bind(4);
				
				m_fullScreenQuad->Render();

				m_previousViewProjectionMatrix = actualViewProjectionMatrix;
			}

			void ShutDown()
			{
				m_hdrSceneNode->ShutDown();
				m_lensFlareSceneNode->ShutDown();

				m_finalCompositorProgram->DeleteShaders();
				m_finalCompositorProgram->Delete();
				SAFE_DELETE(m_finalCompositorProgram);

				m_originFrameBuffer->Delete();
				SAFE_DELETE(m_originFrameBuffer);

				m_fullScreenQuad->Delete();
			}

		public:
			void OnKeyPressedHandler(const OnKeyPress& press)
			{
				if (press.key == GLFW_KEY_F1) m_isEnabled = !m_isEnabled;

				if (press.key == GLFW_KEY_B) m_motionBlurSettings.isEnabled = !m_motionBlurSettings.isEnabled;
				if (press.key == GLFW_KEY_Y) m_motionBlurSettings.maxMotionSamples += 1;
				if (press.key == GLFW_KEY_U) m_motionBlurSettings.maxMotionSamples -= 1;
			}

			void OnKeyReleasedHandler(const OnKeyRelease& release)
			{
			}
		};
	}
}

#endif