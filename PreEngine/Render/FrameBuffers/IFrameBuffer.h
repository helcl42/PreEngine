#ifndef IFRAME_BUFFER_H
#define IFRAME_BUFFER_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			using namespace PreEngine::Render::Textures;

			class IFrameBuffer
			{
			public:
				virtual void Create() = 0;

				virtual bool AddDepthBuffer() = 0;

				virtual bool HasDepthBufferAttached() const = 0;

				virtual void Bind(bool setFullViewport = true) = 0;

				virtual void Delete() = 0;

				virtual void SetFramebufferTextureFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification) = 0;

				virtual void BindFrameBufferTexture(int textureIndex = 0, int textureUnit = 0, bool regenerateMipMaps = false) = 0;

				virtual unsigned int GetWidth() const = 0;

				virtual unsigned int GetHeight() const = 0;

				virtual ITexture* GetTexture(int textureIndex = 0) const = 0;

				virtual GLuint GetHandle() const = 0;

			public:
				virtual ~IFrameBuffer() {}
			};
		}
	}
}

#endif