#include "TextureFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			TextureFactory::TextureFactory()
			{
			}

			TextureFactory::~TextureFactory()
			{
				//for (auto& image : GlobalCache<std::string, FIBITMAP*>::GetInstance().GetAll())
				//{
				//	SAFE_DELETE(image.second);
				//}
			}

			FIBITMAP* TextureFactory::GetImage(const std::string& filePath)
			{
				FIBITMAP* bitmap = NULL;				
				if (!GlobalCache<std::string, FIBITMAP*>::GetInstance().Contains(filePath))
				{
					FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

					fif = FreeImage_GetFileType(filePath.c_str(), 0);

					if (fif == FIF_UNKNOWN)  fif = FreeImage_GetFIFFromFilename(filePath.c_str());

					if (fif == FIF_UNKNOWN) throw TextureException("Unknown Texture format " + filePath + ".");

					if (FreeImage_FIFSupportsReading(fif)) bitmap = FreeImage_Load(fif, filePath.c_str());

					//if (!dib)	throw TextureException("Load HeightMap " + filePath + " failed.");

					GlobalCache<std::string, FIBITMAP*>::GetInstance().Add(filePath, bitmap);
				}
				else
				{
					bitmap = GlobalCache<std::string, FIBITMAP*>::GetInstance().Get(filePath);
				}
				return bitmap;
			}

			GLint TextureFactory::GetMaxMipMapLevel(int width, int height)
			{
				GLint maxMipMapLevel = 1;
				while (width > 1 || height > 1)
				{
					width /= 2;
					height /= 2;
					maxMipMapLevel++;
				}
				return maxMipMapLevel;
			}

			GLint TextureFactory::SetTextureImage(GLubyte* data, int width, int height, GLenum format)
			{
				if (format == GL_RGBA || format == GL_BGRA)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				}
				else if (format == GL_RGB || format == GL_BGR)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				}
				else if (format == GL_RED || format == GL_RG)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				}
				else
				{
					GLint maxMipMapLevel = GetMaxMipMapLevel(width, height);
					glTexStorage2D(GL_TEXTURE_2D, maxMipMapLevel, format, width, height);
					return maxMipMapLevel - 1;
				}

				return GL_TEXTURE_MAX_LEVEL - 1;
			}

			ITexture* TextureFactory::CreateDepthBufferTexture(int width, int height, bool addStencil)
			{
				GLuint depthTexHandle;
				glGenTextures(1, &depthTexHandle);
				glBindTexture(GL_TEXTURE_2D, depthTexHandle);
				glTexImage2D(GL_TEXTURE_2D, 0, addStencil ? GL_DEPTH24_STENCIL8 : GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
				return new Texture(depthTexHandle, width, height);
			}

			Texture* TextureFactory::CreateTextureBase(GLubyte* data, int width, int height, int bpp, GLenum format, bool generateMipMaps)
			{
				GLuint textureId;
				glGenTextures(1, &textureId);
				glBindTexture(GL_TEXTURE_2D, textureId);

				Texture* texture = new Texture(textureId, width, height);
				texture->m_bpp = bpp;
				texture->m_format = format;
				texture->m_data = data;
				texture->m_maxMipMapLevel = SetTextureImage(data, width, height, format);

				if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);									

				unsigned int samplerId;
				glGenSamplers(1, &samplerId);
				texture->m_sampler = samplerId;
				texture->m_initialized = true;
				return texture;
			}

			ITexture* TextureFactory::CreateEmptyTexture(int width, int height, int bpp, GLenum format)
			{
				Texture* texture = CreateTextureBase(NULL, width, height, bpp, format, false);
				texture->m_initialized = false;
				return texture;
			}

			ITexture* TextureFactory::CreateTexture(const std::string& filePath, bool generateMipMaps)
			{
				FIBITMAP* dib = GetImage(filePath);
				if (!dib) return NULL;

				unsigned char* data = FreeImage_GetBits(dib);

				if (data == NULL || FreeImage_GetWidth(dib) == 0 || FreeImage_GetHeight(dib) == 0) throw TextureException("Texture " + filePath + " contains invalid data.");

				unsigned int bpp = FreeImage_GetBPP(dib);

				GLenum format = GL_RGB;
				if (bpp == 32) format = GL_BGRA;
				if (bpp == 24) format = GL_BGR;
				if (bpp == 16) format = GL_RG;
				if (bpp == 8) format = GL_RED;

				return CreateTexture(data, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), bpp, format, generateMipMaps);
			}

			ITexture* TextureFactory::CreateTexture(GLubyte* data, int width, int height, int bpp, GLenum format, bool generateMipMaps)
			{
				Texture* texture = CreateTextureBase(data, width, height, bpp, format, generateMipMaps);
				texture->m_initialized = true;
				return texture;
			}
		}
	}
}