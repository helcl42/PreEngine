#include "FrameBuffer.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			std::map<unsigned int, std::stack<IFrameBuffer*> > FrameBuffer::s_customDefaultFrameBuffers;

			std::map<unsigned int, GLuint> FrameBuffer::s_boundFrameBufferHandles;

			FrameBuffer::FrameBuffer(unsigned int sceneId)
				: m_sceneId(sceneId), m_width(0), m_height(0), m_frameBufferHandle(GL_FALSE), m_depthRenderBufferHandle(GL_FALSE), m_hasDepthBufferAttached(false)
			{
				m_resizeHandler = new EventHandler<FrameBuffer, Windows::Events::OnResize>(this);
			}

			FrameBuffer::~FrameBuffer()
			{
				for (std::vector<ITexture*>::iterator ii = m_frameBufferTextures.begin(); ii != m_frameBufferTextures.end(); ++ii)
				{
					SAFE_DELETE(*ii);
				}

				SAFE_DELETE(m_resizeHandler);
			}

			void FrameBuffer::Create()
			{
				glGenFramebuffers(1, &m_frameBufferHandle);
			}

			bool FrameBuffer::HasDepthBufferAttached() const
			{
				return m_hasDepthBufferAttached;
			}

			bool FrameBuffer::AddDepthBuffer()
			{
				//if (m_hasDepthBufferAttached) return false;
				if (m_frameBufferHandle == GL_FALSE) throw FrameBufferException("Could not add depth buffer to uninitialized frame buffer.");
				if (m_depthRenderBufferHandle != GL_FALSE) throw FrameBufferException("Frame Buffer has already depth buffer attached.");

				glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);

				glGenRenderbuffers(1, &m_depthRenderBufferHandle);
				glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferHandle);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);

				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferHandle);

				return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
			}

			void FrameBuffer::Bind(bool setFullViewport)
			{		
				FrameBuffer::BindFrameBuffer(m_sceneId, m_frameBufferHandle);
				if (setFullViewport)
				{
					glViewport(0, 0, m_width, m_height);
				}
			}

			void FrameBuffer::SetFramebufferTextureFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification)
			{
				for (size_t i = m_hasDepthBufferAttached ? 1 : 0; i < m_frameBufferTextures.size(); i++)
				{
					m_frameBufferTextures[i]->SetFiltering(magnification, minification);
				}	
			}

			ITexture* FrameBuffer::GetTexture(int textureIndex) const
			{
				if (textureIndex >= 0 && textureIndex < (int)m_frameBufferTextures.size())
				{
					return m_frameBufferTextures[textureIndex];
				}
				else
				{
					throw FrameBufferException("Could get texture with index " + textureIndex);
				}
			}

			void FrameBuffer::BindFrameBufferTexture(int textureIndex, int textureUnit, bool regenerateMipMaps)
			{	
				if (textureIndex >= 0 && textureIndex < (int)m_frameBufferTextures.size())
				{
					m_frameBufferTextures[textureIndex]->Bind(textureUnit);
				}
				else
				{
					throw FrameBufferException("Could not bind texture with index " + textureIndex);
				}

				if (regenerateMipMaps)
				{
					glGenerateMipmap(GL_TEXTURE_2D);
				}
			}

			void FrameBuffer::Delete()
			{
				if (m_frameBufferHandle != GL_FALSE)
				{
					glDeleteFramebuffers(1, &m_frameBufferHandle);
					m_frameBufferHandle = GL_FALSE;
				}

				if (m_depthRenderBufferHandle != GL_FALSE)
				{
					glDeleteRenderbuffers(1, &m_depthRenderBufferHandle);
					m_depthRenderBufferHandle = GL_FALSE;
				}

				for (std::vector<ITexture*>::iterator ii = m_frameBufferTextures.begin(); ii != m_frameBufferTextures.end(); ++ii)
				{
					(*ii)->Delete();
				}

				if (s_boundFrameBufferHandles.find(m_sceneId) == s_boundFrameBufferHandles.end())
				{
					s_boundFrameBufferHandles.erase(m_sceneId);
				}
			}

			unsigned int FrameBuffer::GetWidth() const
			{
				return m_width;
			}

			unsigned int FrameBuffer::GetHeight() const
			{
				return m_height;
			}

			GLuint FrameBuffer::GetHandle() const
			{
				return m_frameBufferHandle;
			}

			void FrameBuffer::BindFrameBuffer(unsigned int sceneId, GLuint frameBufferHandle)
			{
				if (s_boundFrameBufferHandles.find(sceneId) == s_boundFrameBufferHandles.end())
				{					
					glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
					s_boundFrameBufferHandles.insert(std::make_pair(sceneId, frameBufferHandle));
				}
				else
				{
					if (s_boundFrameBufferHandles[sceneId] != frameBufferHandle)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
						s_boundFrameBufferHandles[sceneId] = frameBufferHandle;
					}
				}
			}

			void FrameBuffer::BindDefaultFrameBuffer(unsigned int sceneId, int width, int height)
			{
				BindDefaultFrameBuffer(sceneId, 0, 0, width, height);
			}

			void FrameBuffer::BindDefaultFrameBuffer(unsigned int sceneId, int offsetX, int offsetY, int width, int height)
			{
				if (s_customDefaultFrameBuffers.find(sceneId) != s_customDefaultFrameBuffers.end() && !s_customDefaultFrameBuffers[sceneId].empty())
				{
					IFrameBuffer* currentDefaultFrameBuffer = s_customDefaultFrameBuffers[sceneId].top();
					FrameBuffer::BindFrameBuffer(sceneId, currentDefaultFrameBuffer->GetHandle());
					s_customDefaultFrameBuffers[sceneId].pop();
				}
				else
				{
					FrameBuffer::BindFrameBuffer(sceneId, 0);
				}
				EventChannel::Broadcast(Frustums::Events::OnResize{ (int)sceneId, offsetX, offsetY, width, height });
			}

			void FrameBuffer::ResetGlobalState()
			{
				s_customDefaultFrameBuffers.clear();
				s_boundFrameBufferHandles.clear();
			}

			void FrameBuffer::SetCustomDefaultFrameBuffer(unsigned int sceneId, IFrameBuffer* customDefaultFrameBuffer)
			{
				if (customDefaultFrameBuffer != NULL)
				{
					if (s_customDefaultFrameBuffers.find(sceneId) == s_customDefaultFrameBuffers.end())
					{
						std::stack<IFrameBuffer*> newStack;
						newStack.push(customDefaultFrameBuffer);
						s_customDefaultFrameBuffers.insert(std::make_pair(sceneId, newStack));
					}
					else
					{
						s_customDefaultFrameBuffers[sceneId].push(customDefaultFrameBuffer);
					}
				}
				else
				{
					if (s_customDefaultFrameBuffers.find(sceneId) != s_customDefaultFrameBuffers.end() && !s_customDefaultFrameBuffers[sceneId].empty())
					{
						s_customDefaultFrameBuffers[sceneId].pop();
					}
					else
					{
						s_customDefaultFrameBuffers.erase(sceneId);
					}
				}
			}

			IFrameBuffer* FrameBuffer::GetCurrentDefaultFrameBuffer(unsigned int sceneId)
			{
				if (s_customDefaultFrameBuffers.find(sceneId) != s_customDefaultFrameBuffers.end() && !s_customDefaultFrameBuffers[sceneId].empty())
				{
					return s_customDefaultFrameBuffers[sceneId].top();
				}
				return NULL; // real gl context default FrameBuffer
			}

			void FrameBuffer::operator() (const Windows::Events::OnResize& resize)
			{
				/*m_width = (m_width / resize.width) * m_width;
				if (m_width > resize.width) m_width = resize.width;

				m_height = (m_height / resize.height) * m_height;
				if (m_height > resize.height) m_height = resize.height;*/

				// TODO resize texture by new measures
			}
		}
	}
}
