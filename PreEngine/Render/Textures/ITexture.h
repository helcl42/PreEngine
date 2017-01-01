#ifndef ITEXTURE_H
#define ITEXTURE_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			class ITexture
			{
			public:
				virtual void SetFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification) = 0;

				virtual MinificationTextureFilterType GetMinificationFilter() const = 0;

				virtual MagnificationTextureFilterType GetMagnificationFilter() const = 0;

				virtual void Delete() = 0;

				virtual void Bind(int textureUnit = 0) = 0;

				virtual void SetSamplerParameter(GLenum parameter, GLenum value) = 0;

				virtual unsigned int GetWidth() const = 0;

				virtual unsigned int GetHeight() const = 0;

				virtual unsigned int GetBpp() const = 0;

				virtual GLubyte* GetData() const = 0;

				virtual GLint GetMaxMipMapLevel() const = 0;

				virtual unsigned int GetHandle() const = 0;

				virtual GLenum GetFormat() const = 0;

				virtual void SetWrap(GLint value) = 0;

				virtual unsigned int GetSampler() const = 0;

				virtual std::string GetPath() const = 0;

				virtual void Update(unsigned int w, unsigned int h, GLvoid* data, GLenum inputDataFormat, GLint internalFormat, bool generateMipMaps) = 0;

				virtual bool IsInitialized() const = 0;

			public:
				virtual ~ITexture() {}
			};
		}
	}
}

#endif