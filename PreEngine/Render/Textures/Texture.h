#ifndef TEXTURE_H
#define TEXTURE_H

#include "MagnificationTextureFilterType.h"
#include "MinificationTextureFilterType.h"
#include "TextureException.h"
#include "ITexture.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			class Texture : public ITexture
			{
			private:
				friend class TextureFactory;

			private:
				unsigned int m_width;

				unsigned int m_height;

				unsigned int m_bpp;

				GLenum m_format;

				GLubyte* m_data;

				GLint m_maxMipMapLevel;

				unsigned int m_handle;

				unsigned int m_sampler;

				MinificationTextureFilterType m_minificationFilter;

				MagnificationTextureFilterType m_magnificationFilter;

				std::string m_path;

				bool m_initialized;

			public:
				Texture();

				Texture(unsigned int handle, unsigned int width, unsigned int height);

				virtual ~Texture();

			public:
				void SetFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification);

				int GetMinificationFilter() const;

				int GetMagnificationFilter() const;

				void Delete();

				void Bind(int textureUnit = 0);

				void Unbind();

				void SetSamplerParameter(GLenum parameter, GLenum value);

				void SetWrap();

				unsigned int GetWidth() const;

				unsigned int GetHeight() const;

				unsigned int GetBpp() const;

				GLint GetMaxMipMapLevel() const;

				GLubyte* GetData() const;

				unsigned int GetHandle() const;

				GLenum GetFormat() const;

				unsigned int GetSampler() const;

				std::string GetPath() const;

				void Update(unsigned int w, unsigned int h, GLvoid* data, bool generateMipMaps, GLenum format = GL_RGB);

				bool IsInitialized() const;
			};
		}
	}
}

#endif