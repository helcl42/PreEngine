#include "Texture.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			Texture::Texture()
				: Texture(0, 0, 0)
			{
			}

			Texture::Texture(unsigned int handle, unsigned int width, unsigned int height)
				: m_handle(handle), m_width(width), m_height(height), m_bpp(0), m_data(NULL), m_sampler(0), m_initialized(false)
			{
			}

			Texture::~Texture()
			{
			}

			void Texture::SetFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification)
			{
				glBindSampler(0, m_sampler);

				// Set magnification filter
				if (magnification == MagnificationTextureFilterType::TEXTURE_FILTER_MAG_NEAREST)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				else if (magnification == MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				else
					throw new TextureException("Invalid magnification filter: " + magnification);

				// Set minification filter
				if (minification == MinificationTextureFilterType::TEXTURE_FILTER_MIN_NEAREST)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				else if (minification == MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				else if (minification == MinificationTextureFilterType::TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				else if (minification == MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				else if (minification == MinificationTextureFilterType::TEXTURE_FILTER_MIN_TRILINEAR)
					glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				else
					throw new TextureException("Invalid minification filter: " + minification);

				m_minificationFilter = minification;
				m_magnificationFilter = magnification;

				GLfloat maxAnisotropyFilterFactor = 0.0f;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropyFilterFactor);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropyFilterFactor);
			}

			int Texture::GetMinificationFilter() const
			{
				return m_minificationFilter;
			}

			int Texture::GetMagnificationFilter() const
			{
				return m_magnificationFilter;
			}

			void Texture::SetSamplerParameter(GLenum parameter, GLenum value)
			{
				glSamplerParameteri(m_sampler, parameter, value);
			}

			void Texture::Bind(int textureUnit)
			{
				glActiveTexture(GL_TEXTURE0 + textureUnit);
				glBindTexture(GL_TEXTURE_2D, m_handle);
				glBindSampler(textureUnit, m_sampler);
			}

			void Texture::Unbind()
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			void Texture::Delete()
			{
				glDeleteSamplers(1, &m_sampler);
				glDeleteTextures(1, &m_handle);
			}

			void Texture::SetWrap()
			{
				glBindSampler(0, m_sampler);
				glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			unsigned int Texture::GetWidth() const
			{
				return m_width;
			}

			unsigned int Texture::GetHeight() const
			{
				return m_height;
			}

			unsigned int Texture::GetBpp() const
			{
				return m_bpp;
			}

			GLubyte* Texture::GetData() const
			{
				return m_data;
			}

			GLint Texture::GetMaxMipMapLevel() const
			{
				return m_maxMipMapLevel;
			}

			unsigned int Texture::GetHandle() const
			{
				return m_handle;
			}

			unsigned int Texture::GetSampler() const
			{
				return m_sampler;
			}

			std::string Texture::GetPath() const
			{
				return m_path;
			}

			GLenum Texture::GetFormat() const
			{
				return m_format;
			}

			void Texture::SetInstance(unsigned int w, unsigned int h, GLvoid* data, bool generateMipMaps, GLenum format)
			{
				if (m_initialized)
				{
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, format, GL_UNSIGNED_BYTE, (GLvoid*)data);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, (GLvoid*)data);
					m_initialized = true;
				}

				m_width = w;
				m_height = h;
				m_data = (GLubyte*)data;
				m_format = format;

				if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);
			}

			bool Texture::IsInitialized() const
			{
				return m_initialized;
			}
		}
	}
}