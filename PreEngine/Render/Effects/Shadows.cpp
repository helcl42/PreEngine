#include "Shadows.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Effects
		{
			Shadows::Shadows(int sceneId)
				: Shadows(sceneId, 2048, true, false)
			{
			}

			Shadows::Shadows(int sceneId, unsigned int shadowTextureSize, bool shadowsOn, bool useHardShadows)
				: m_shadowMapTextureSize(shadowTextureSize), m_shadowMapFrameBuffer(NULL), m_shadowsOn(shadowsOn), m_useHardShadows(useHardShadows), m_sceneId(sceneId)
			{
				m_frameBufferFactory = new FrameBufferFactory();
			}

			Shadows::~Shadows()
			{
				SAFE_DELETE(m_shadowMapFrameBuffer);
				SAFE_DELETE(m_frameBufferFactory);				
			}

			void Shadows::Init()
			{
				m_shadowMapFrameBuffer = m_frameBufferFactory->CreateFrameBuffer(m_sceneId, m_shadowMapTextureSize, m_shadowMapTextureSize, std::vector<GLenum> {}, true);
			}

			void Shadows::ShutDown()
			{
				m_shadowMapFrameBuffer->Delete();
			}

			void Shadows::BindFrameBuffer(bool useFullViewPort)
			{
				m_shadowMapFrameBuffer->Bind(useFullViewPort);
			}

			void Shadows::BindFrameBufferTexture()
			{
				m_shadowMapFrameBuffer->BindFrameBufferTexture(0, m_textureUnit, false);
			}

			void Shadows::SetUniformData(IShaderProgram* shaderProgram, const std::string& shadowsVariableName)
			{
				shaderProgram->SetUniform(shadowsVariableName + ".shadowsOn", m_shadowsOn);
				shaderProgram->SetUniform(shadowsVariableName + ".useHardShadows", m_useHardShadows);
				shaderProgram->SetUniform("gShadowMap", m_textureUnit); // NOT CLEAN !!!
			}

			void Shadows::ToggleShadowsOn()
			{
				m_shadowsOn = !m_shadowsOn;
			}

			void Shadows::SetShadowsOn(bool val)
			{
				m_shadowsOn = val;
			}

			bool Shadows::AreShadowOn() const
			{
				return m_shadowsOn;
			}

			void Shadows::ToggleUsehardShadows()
			{
				m_useHardShadows = !m_useHardShadows;
			}

			void Shadows::UseHardShadows(bool val)
			{
				m_useHardShadows = val;
			}

			bool Shadows::AreUsedHardShadows() const
			{
				return m_useHardShadows;
			}

			int Shadows::GetTextureUnit() const
			{
				return m_textureUnit;
			}

			void Shadows::SetTextureUnit(int textureUnit)
			{
				m_textureUnit = textureUnit;
			}
		}
	}
}