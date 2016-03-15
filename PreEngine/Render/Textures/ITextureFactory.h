#ifndef ITEXTURE_FACTORY_H
#define ITEXTURE_FACTORY_H

#include "../../Core/Common.h"
#include "TextureException.h"
#include "Texture.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			class ITextureFactory
			{
			public:
				virtual ITexture* CreateEmptyTexture(int width, int height, int bpp, GLenum format) = 0;

				virtual ITexture* CreateDepthBufferTexture(int width, int height) = 0;

				virtual ITexture* CreateTexture(const std::string& filePath, bool generateMipMaps = false) = 0;

				virtual ITexture* CreateTexture(GLubyte* data, int width, int height, int bpp, GLenum format, bool generateMipMaps) = 0;

			public:
				virtual ~ITextureFactory() {}
			};
		}
	}
}

#endif