#ifndef ABSTRACT_TEXTURE_FACTORY_H
#define ABSTRACT_TEXTURE_FACTORY_H

#include "ITextureFactory.h"

#include <FreeImage.h>

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			class TextureFactory : public ITextureFactory
			{
			public:
				TextureFactory();

				virtual ~TextureFactory();

			private:
				GLint GetMaxMipMapLevel(int width, int height);

				FIBITMAP* GetImage(const std::string& filePath);

				GLint SetTextureImage(GLubyte* data, int width, int height, GLenum format);

				Texture* CreateTextureBase(GLubyte* data, int width, int height, int bpp, GLenum format, bool generateMipMaps);

			public:
				ITexture* CreateEmptyTexture(int width, int height, int bpp, GLenum format);

				ITexture* CreateDepthBufferTexture(int width, int height);

				ITexture* CreateTexture(const std::string& filePath, bool generateMipMaps = false);

				ITexture* CreateTexture(GLubyte* data, int width, int height, int bpp, GLenum format, bool generateMipMaps);
			};
		}
	}
}

#endif