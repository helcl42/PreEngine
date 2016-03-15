#ifndef SHADOWS_H

#define SHADOWS_H

#include "../../Core/Common.h"
#include "../../Render/Shaders/ShaderProgram.h"
#include "../../Render/FrameBuffers/FrameBufferFactory.h"

#include "IEffect.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Effects
		{
			using namespace PreEngine::Render::Shaders;
			using namespace PreEngine::Render::FrameBuffers;

			class Shadows : public IEffect
			{
			private:
				unsigned int m_shadowMapTextureSize = 2048;

				IFrameBuffer* m_shadowMapFrameBuffer = NULL;

				IFrameBufferFactory* m_frameBufferFactory = NULL;

				bool m_shadowsOn = true;

				bool m_useHardShadows = false;

				int m_textureUnit = 0;

				int m_sceneId = 0;

			public:
				Shadows(int sceneId);
				
				Shadows(int sceneId, unsigned int shadowTextureSize, bool shadowsOn, bool useHardShadows);

				virtual ~Shadows();

			public:
				void Init();

				void ShutDown();

			public:
				void BindFrameBuffer(bool useFullViewPort = true);

				void BindFrameBufferTexture();

				void SetUniformData(IShaderProgram* shaderProgram, const std::string& shadowsVariableName);

			public:
				void ToggleShadowsOn();

				void SetShadowsOn(bool val);

				bool AreShadowOn() const;

				void ToggleUsehardShadows();

				void UseHardShadows(bool val);

				bool AreUsedHardShadows() const;

				int GetTextureUnit() const;

				void SetTextureUnit(int textureUnit);
			};
		}
	}
}

#endif