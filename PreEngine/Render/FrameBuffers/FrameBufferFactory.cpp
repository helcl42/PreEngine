#include "FrameBufferFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			FrameBufferFactory::FrameBufferFactory()
			{
				m_textureFactory = new TextureFactory();
			}

			FrameBufferFactory::~FrameBufferFactory()
			{
				SAFE_DELETE(m_textureFactory);
			}

			FrameBuffer* FrameBufferFactory::CreateFrameBufferBase(int sceneId, int width, int height)
			{
				FrameBuffer* frameBuffer = new FrameBuffer(sceneId);
				frameBuffer->Create();
				frameBuffer->Bind(false);
				frameBuffer->m_width = width;
				frameBuffer->m_height = height;
				return frameBuffer;
			}

			void FrameBufferFactory::AttachColorTexture(FrameBuffer* frameBuffer, int width, int height, GLenum format, GLenum attachmentIndex)
			{
				ITexture* texture = m_textureFactory->CreateEmptyTexture(width, height, 8, format); // fake bpp :)
				if (texture != NULL)
				{
					frameBuffer->m_frameBufferTextures.push_back(texture);
					glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentIndex, GL_TEXTURE_2D, texture->GetHandle(), 0);
				}
				else
				{
					throw new FrameBufferException("Creation of frame buffer texture failed");
				}
			}

			void FrameBufferFactory::AttachDepthTexture(FrameBuffer* frameBuffer, int width, int height)
			{
				ITexture* depthTexture = m_textureFactory->CreateDepthBufferTexture(width, height);
				if (depthTexture != NULL)
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->GetHandle(), 0);
					frameBuffer->m_frameBufferTextures.push_back(depthTexture);
					frameBuffer->m_hasDepthBufferAttached = true;
				}
				else
				{
					throw new FrameBufferException("Creation of frame buffer texture failed");
				}
			}

			void FrameBufferFactory::SetDrawBuffers(int colorAttachmentsCount, bool depthAttachment)
			{
				if (colorAttachmentsCount == 0 && depthAttachment)
				{
					GLenum drawBuffers[] = { GL_NONE };
					glDrawBuffers(1, drawBuffers);
				}
				else
				{
					GLenum* drawBuffers = new GLenum[colorAttachmentsCount];
					for (int i = 0; i < colorAttachmentsCount; i++)
					{
						drawBuffers[i] = GL_COLOR_ATTACHMENT0 + int(i);
					}
					glDrawBuffers(colorAttachmentsCount, drawBuffers);
					SAFE_DELETE_ARRAY(drawBuffers);
				}
			}

			IFrameBuffer* FrameBufferFactory::CreateFrameBuffer(int sceneId, int width, int height, std::vector<GLenum> formats, bool attachDepthBuffer)
			{
				FrameBuffer* frameBuffer = CreateFrameBufferBase(sceneId, width, height);
				
				if (attachDepthBuffer)
				{
					AttachDepthTexture(frameBuffer, width, height);
				}

				for (size_t i = 0; i < formats.size(); i++)
				{
					AttachColorTexture(frameBuffer, width, height, formats[i], GL_COLOR_ATTACHMENT0 + int(i));
				}				

				SetDrawBuffers((int)formats.size(), attachDepthBuffer);
		
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw new FrameBufferException("Creation of frame buffer failed");

				return frameBuffer;
			}
		}
	}
}