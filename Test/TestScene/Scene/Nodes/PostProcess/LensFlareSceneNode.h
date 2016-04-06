#ifndef LENS_FLARE_SCENE_NODE_H
#define LENS_FLARE_SCENE_NODE_H

#include <PreEngine/Render/Models/Primitives/Quad.h>

#include "../BaseSceneNode.h"
#include "LensFlareSettings.h"

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
		class LensFlareSceneNode : public BaseSceneNode<LensFlareSceneNode<RootType>, RootType>, public IKeyboardListener
		{
		private:
			IFrameBuffer* m_lensOriginFrameBuffer;

			IFrameBuffer* m_resultFrameBuffer;

			IFrameBuffer* m_tempFrameBuffer;


			IShaderProgram* m_downSampleBiasProgram;

			IShaderProgram* m_ghostsProgram;

			IShaderProgram* m_gaussianBlurProgram;


			ITextureFactory* m_textureFactory;

			ITexture* m_lensColorTexture;

			ITexture* m_lensDirtTexture;

			ITexture* m_lensStarTexture;

			IInputFacade* m_inputFacade;


			Quad *m_fullScreenQuad;

			LensFlareSettings m_settings;

			
		public:
			LensFlareSceneNode(RootType* root)
				: BaseSceneNode<LensFlareSceneNode<RootType>, RootType>(root)
			{
				m_inputFacade = new InputFacade();
				m_inputFacade->RegisterKeyboardListener(this);

				m_textureFactory = new TextureFactory();
			}

			virtual ~LensFlareSceneNode()
			{
				SAFE_DELETE(m_textureFactory);
				SAFE_DELETE(m_lensStarTexture);
				SAFE_DELETE(m_lensDirtTexture);
				SAFE_DELETE(m_lensColorTexture);
				SAFE_DELETE(m_gaussianBlurProgram);
				SAFE_DELETE(m_ghostsProgram);
				SAFE_DELETE(m_downSampleBiasProgram);
				SAFE_DELETE(m_inputFacade);
				SAFE_DELETE(m_lensOriginFrameBuffer);
				SAFE_DELETE(m_resultFrameBuffer);
				SAFE_DELETE(m_tempFrameBuffer);
				SAFE_DELETE(m_fullScreenQuad);
			}

			void InitShaders()
			{
				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/LensFlareGhostsShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/LensFlare/Ghosts.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/LensFlare/Ghosts.frag.hlsl");
				m_ghostsProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/LensFlareDownsampleScaleShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/LensFlare/DownsampleScale.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/LensFlare/DownsampleScale.frag.hlsl");
				m_downSampleBiasProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/LensFlareGaussianBlurShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/LensFlare/GaussianBlur.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/LensFlare/GaussianBlur.frag.hlsl");
				m_gaussianBlurProgram = m_programBuilder->Build();
			}

			void InitTextures()
			{
				m_lensColorTexture = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/lenscolor.png", true);
				m_lensDirtTexture = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/lensdirt.png", true);
				m_lensStarTexture = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/lensstar.png", true);
			}

			void InitFrameBuffers()
			{
				FrameBufferFactory frameBufferFactory;
				m_lensOriginFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_RGB });
				m_lensOriginFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR);

				m_resultFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_RGB });
				m_resultFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR);

				m_tempFrameBuffer = frameBufferFactory.CreateFrameBuffer(m_sceneId, m_width, m_height, std::vector<GLenum> { GL_RGB });
				m_tempFrameBuffer->SetFramebufferTextureFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR);
			}

		public:
			void Init()
			{
				m_fullScreenQuad = new Quad();
				m_fullScreenQuad->Init();

				InitShaders();
				InitFrameBuffers();
				InitTextures();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;
				ss << "Lens Flare: " << (m_settings.isEnabled ? "ON" : "OFF") << std::endl;
				ss << "Mode: " << (m_settings.mode == LensFlareMode::SIMPLE ? "SIMPLE" : m_settings.mode == LensFlareMode::WITH_HEJL ? "WITH HEJL" : "WITH STARBURST") << std::endl;
				ss << "---------------------------------------" << std::endl;
				/*ss << "Scale: " << m_settings.scale << std::endl;
				ss << "Bias: " << m_settings.bias << std::endl;
				ss << "---------------------------------------" << std::endl;
				ss << "Ghosts: " << m_settings.countOfGhosts << std::endl;
				ss << "Ghosts Disperal: " << m_settings.ghostDisperal << std::endl;
				ss << "Halo Width: " << m_settings.haloWidth << std::endl;
				ss << "Distortion Coefficient: " << m_settings.distortionCoefficient << std::endl;
				ss << "---------------------------------------" << std::endl;
				ss << "Blur Radius: " << m_settings.blurRadius << std::endl;
				ss << "---------------------------------------" << std::endl;*/
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
			}

			void PreRender()
			{
				m_lensOriginFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				

				if (!m_settings.isEnabled) return;

				//////////////////////////////////////////////////////////////
				/// Sun like render
				//////////////////////////////////////////////////////////////
				glEnable(GL_DEPTH_TEST);
				FindSingleByType<SunSceneNode<RootType>>()->Render();
			}

			void Render()
			{

			}

			void PostRender()
			{
				m_resultFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				if (!m_settings.isEnabled) return;

				//////////////////////////////////////////////////////////////
				/// Downsample + Scale
				//////////////////////////////////////////////////////////////
				m_tempFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_downSampleBiasProgram->Use();
				m_downSampleBiasProgram->SetUniform("scale", glm::vec4(m_settings.scale));
				m_downSampleBiasProgram->SetUniform("bias", glm::vec4(m_settings.bias));
				m_downSampleBiasProgram->SetUniform("gSampler", 0);
				SetMatrices(m_downSampleBiasProgram);
				m_lensOriginFrameBuffer->BindFrameBufferTexture(0, 0, true);
				m_fullScreenQuad->Render();

				////////////////////////////////////////////////////////////////
				///// Ghosts Halo
				////////////////////////////////////////////////////////////////
				m_resultFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_ghostsProgram->Use();
				m_ghostsProgram->SetUniform("ghosts", m_settings.countOfGhosts);
				m_ghostsProgram->SetUniform("ghostDispersal", m_settings.ghostDisperal);
				m_ghostsProgram->SetUniform("haloWidth", m_settings.haloWidth);
				m_ghostsProgram->SetUniform("distortionCoef", m_settings.distortionCoefficient);
				m_ghostsProgram->SetUniform("gSampler", 0);
				m_ghostsProgram->SetUniform("gLensColorSampler", 1);
				SetMatrices(m_ghostsProgram);

				m_tempFrameBuffer->BindFrameBufferTexture(0, 0, true);
				m_lensColorTexture->Bind(1);
				m_fullScreenQuad->Render();

				////////////////////////////////////////////////////////////////
				///// Gaussian Blur X pass
				////////////////////////////////////////////////////////////////
				m_tempFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_gaussianBlurProgram->Use();
				m_gaussianBlurProgram->SetUniform("gSampler", 0);
				m_gaussianBlurProgram->SetUniform("blurRadius", m_settings.blurRadius);
				m_gaussianBlurProgram->SetUniform("blurDirection", glm::vec2(1.0f, 0.0f));
				SetMatrices(m_gaussianBlurProgram);
				m_resultFrameBuffer->BindFrameBufferTexture(0, 0, true);
				m_fullScreenQuad->Render();

				////////////////////////////////////////////////////////////////
				///// Gaussian Blur Y pass
				////////////////////////////////////////////////////////////////
				m_resultFrameBuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_projection = glm::mat4(1.0);
				m_view = glm::mat4(1.0);
				m_model = glm::mat4(1.0);

				m_gaussianBlurProgram->Use();
				m_ghostsProgram->SetUniform("gSampler", 0);
				m_gaussianBlurProgram->SetUniform("blurRadius", m_settings.blurRadius);
				m_gaussianBlurProgram->SetUniform("blurDirection", glm::vec2(0.0f, 1.0f));
				SetMatrices(m_gaussianBlurProgram);

				m_tempFrameBuffer->BindFrameBufferTexture(0, 0, true);
				m_fullScreenQuad->Render();
			}

			void ShutDown()
			{
				m_lensColorTexture->Delete();
				m_lensDirtTexture->Delete();
				m_lensStarTexture->Delete();

				m_downSampleBiasProgram->DeleteShaders();
				m_downSampleBiasProgram->Delete();
				SAFE_DELETE(m_downSampleBiasProgram);

				m_ghostsProgram->DeleteShaders();
				m_ghostsProgram->Delete();
				SAFE_DELETE(m_ghostsProgram);

				m_gaussianBlurProgram->DeleteShaders();
				m_gaussianBlurProgram->Delete();
				SAFE_DELETE(m_gaussianBlurProgram);

				m_resultFrameBuffer->Delete();
				SAFE_DELETE(m_resultFrameBuffer);

				m_tempFrameBuffer->Delete();
				SAFE_DELETE(m_tempFrameBuffer);

				m_lensOriginFrameBuffer->Delete();
				SAFE_DELETE(m_lensOriginFrameBuffer);
				
				m_fullScreenQuad->Delete();
				SAFE_DELETE(m_fullScreenQuad);
			}

			IFrameBuffer* GetLensOriginFrameBuffer() const
			{
				return m_lensOriginFrameBuffer;
			}

			IFrameBuffer* GetResultFrameBuffer() const
			{
				return m_resultFrameBuffer;
			}

			LensFlareMode GetMode() const
			{
				return m_settings.mode;
			}

			glm::mat4 GetStarRotationMatrix() const
			{
				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();

				glm::mat4 starRotationMatrix(1.0);
				starRotationMatrix = glm::translate(starRotationMatrix, glm::vec3(-0.5f, -0.5f, 0.0f));
				starRotationMatrix = glm::rotate(starRotationMatrix, glm::radians(camera->GetCamera()->GetAngleX()), glm::vec3(1.0f, 0.0f, 0.0f));
				starRotationMatrix = glm::rotate(starRotationMatrix, glm::radians(camera->GetCamera()->GetAngleY()), glm::vec3(0.0f, 0.0f, 1.0f));
				starRotationMatrix = glm::translate(starRotationMatrix, glm::vec3(0.5f, 0.5f, 0.0f));
				return starRotationMatrix;
			}

			bool ShouldShowLensSource() const
			{
				return m_settings.showLensSource;
			}

			ITexture* GetLensDirtTexture() const
			{
				return m_lensDirtTexture;
			}

			ITexture* GetLensStarTexture() const
			{
				return m_lensStarTexture;
			}

		public:
			void OnKeyPressedHandler(const OnKeyPress& press)
			{
				if (press.key == GLFW_KEY_I) m_settings.mode = LensFlareMode::SIMPLE;
				else if (press.key == GLFW_KEY_O) m_settings.mode = LensFlareMode::WITH_HEJL;
				else if (press.key == GLFW_KEY_P) m_settings.mode = LensFlareMode::WITH_HEJL_AND_STARBURST;

				if (press.key == GLFW_KEY_Q) m_settings.isEnabled = !m_settings.isEnabled;
			}

			void OnKeyReleasedHandler(const OnKeyRelease& release)
			{
			}
		};
	}
}

#endif