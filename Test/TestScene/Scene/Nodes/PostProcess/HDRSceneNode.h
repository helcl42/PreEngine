#ifndef HDR_SCENE_NODE_H
#define HDR_SCENE_NODE_H

#include <PreEngine/Render/Models/Primitives/Quad.h>

#include "../BaseSceneNode.h"
#include "HDRSettings.h"

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
		class HDRSceneNode : public BaseSceneNode<HDRSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			IFrameBuffer* m_sourceFrameBuffer;

			IFrameBuffer* m_hdrAverageLuminanceFrameBuffer;

			IFrameBuffer* m_hdrResultFrameBuffer;


			IShaderProgram* m_hdrPreprocessProgram;

			IShaderProgram* m_hdrPostprocessProgram;


			IInputFacade* m_inputFacade;


			Quad *m_fullScreenQuad;

			HDRSettings m_hdrSettings;

		public:
			HDRSceneNode(RootType* root)
				: BaseSceneNode<HDRSceneNode<RootType>, RootType>(root)
			{
				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);
			}

			virtual ~HDRSceneNode()
			{
				SAFE_DELETE(m_inputFacade);
			}

		private:
			void InitShaders()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/PostProcessHDRPreProcessShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/HDR/HDRPreProcess.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/HDR/HDRPreProcess.frag.hlsl");
				m_hdrPreprocessProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/PostProcessHDRPostProcessShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/HDR/HDRPostprocess.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/HDR/HDRPostprocess.frag.hlsl");
				m_hdrPostprocessProgram = m_programBuilder->Build();
			}

			void InitFrameBuffers()
			{
				FrameBufferFactory frameBufferFactory;

				m_hdrResultFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_RGB32F }, true);
				m_hdrResultFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR);

				m_hdrAverageLuminanceFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_R32F }, true);
				m_hdrAverageLuminanceFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
			}

		public:
			void Init()
			{
				m_fullScreenQuad = new Quad();
				m_fullScreenQuad->Init();

				InitShaders();
				InitFrameBuffers();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;				
				ss << "HDR: " << (m_hdrSettings.isEnabled ? "ON" : "OFF") << std::endl;
				ss << "HDR Average luminance: " << m_hdrSettings.averageLuminance << std::endl;
				ss << "HDR Exposure: " << m_hdrSettings.exposure << std::endl;
				ss << "HDR White: " << m_hdrSettings.white << std::endl;
				ss << "---------------------------------------" << std::endl;
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				const float HDR_EXPOSURE_OFFSET = 0.1f;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_K)) m_hdrSettings.exposure += HDR_EXPOSURE_OFFSET * m_deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_L)) m_hdrSettings.exposure -= HDR_EXPOSURE_OFFSET * m_deltaTime;

				const float HDR_WHITE_OFFSET = 0.1f;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_O)) m_hdrSettings.white += HDR_WHITE_OFFSET * m_deltaTime;
				if (m_inputFacade->IsKeyPressed(GLFW_KEY_P)) m_hdrSettings.white -= HDR_WHITE_OFFSET * m_deltaTime;
			}

			void PreRender()
			{
			}

			void Render()
			{

			}

			void PostRender()
			{
				if (!m_hdrSettings.isEnabled) return;

				glm::mat4 actualViewProjectionMatrix = m_projection * m_view;

				//////////////////////////////////////////////////////////////
				/// Obtain average luminance
				//////////////////////////////////////////////////////////////
				m_hdrAverageLuminanceFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_model = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_projection = glm::mat4(1.0);

				m_hdrPreprocessProgram->Use();
				m_hdrPreprocessProgram->SetUniform("inputTex", 0);
				m_hdrPreprocessProgram->SetUniform("hdrEnabled", m_hdrSettings.isEnabled);
				m_sourceFrameBuffer->BindFrameBufferTexture(1, 0, true);
				SetMatrices(m_hdrPreprocessProgram);
				m_fullScreenQuad->Render();

				glGetTexImage(GL_TEXTURE_2D, m_hdrAverageLuminanceFrameBuffer->GetTexture(1)->GetMaxMipMapLevel(), GL_RED, GL_FLOAT, &m_hdrSettings.averageLuminance);

				//////////////////////////////////////////////////////////////
				/// Apply HDR
				//////////////////////////////////////////////////////////////
				m_hdrResultFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_hdrPostprocessProgram->Use();
				m_hdrPostprocessProgram->SetUniform("inputTex", 0);
				m_hdrPostprocessProgram->SetUniform("hdrEnabled", m_hdrSettings.isEnabled);
				m_hdrPostprocessProgram->SetUniform("averageLuminance", m_hdrSettings.averageLuminance);
				m_hdrPostprocessProgram->SetUniform("exposure", m_hdrSettings.exposure);
				m_hdrPostprocessProgram->SetUniform("white", m_hdrSettings.white);
				m_sourceFrameBuffer->BindFrameBufferTexture(1, 0, true);
				SetMatrices(m_hdrPostprocessProgram);
				m_fullScreenQuad->Render();
			}

			void ShutDown()
			{
				m_hdrPreprocessProgram->DeleteShaders();
				m_hdrPreprocessProgram->Delete();
				SAFE_DELETE(m_hdrPreprocessProgram);

				m_hdrPostprocessProgram->DeleteShaders();
				m_hdrPostprocessProgram->Delete();
				SAFE_DELETE(m_hdrPostprocessProgram);

				m_hdrResultFrameBuffer->Delete();
				SAFE_DELETE(m_hdrResultFrameBuffer);

				m_hdrAverageLuminanceFrameBuffer->Delete();
				SAFE_DELETE(m_hdrAverageLuminanceFrameBuffer);

				m_fullScreenQuad->Delete();
				SAFE_DELETE(m_fullScreenQuad);
			}

			void SetSourceFrameBuffer(IFrameBuffer* sourceFrameBuffer)
			{
				m_sourceFrameBuffer = sourceFrameBuffer;
			}

			IFrameBuffer* GetResultFrameBuffer() const
			{
				return m_hdrSettings.isEnabled ? m_hdrResultFrameBuffer : m_sourceFrameBuffer;
			}

		public:
			void OnKeyPressedHandler(const OnKeyPress& press)
			{
				if (press.key == GLFW_KEY_N) m_hdrSettings.isEnabled = !m_hdrSettings.isEnabled;
			}

			void OnKeyReleasedHandler(const OnKeyRelease& release)
			{
			}
		};
	}
}

#endif