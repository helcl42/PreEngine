#ifndef FRAME_BUFFER_FACTORY_H
#define FRAME_BUFFER_FACTORY_H

#include "../Textures/TextureFactory.h"
#include "FrameBuffer.h"
#include "IFrameBufferFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			using namespace PreEngine::Render::Textures;

			class FrameBufferFactory : public IFrameBufferFactory
			{
			private:
				ITextureFactory* m_textureFactory;

			public:
				FrameBufferFactory();

				virtual ~FrameBufferFactory();

			private:
				FrameBuffer* CreateFrameBufferBase(int sceneId, int width, int height);

				void AttachColorTexture(FrameBuffer* frameBuffer, int width, int height, GLenum format, GLenum attachmentIndex);

				void AttachDepthTexture(FrameBuffer* frameBuffer, int width, int height, bool addStencil);

				void SetDrawBuffers(int colorAttachmentsCount, bool depthAttachment);

			public:				
				IFrameBuffer* CreateFrameBuffer(int sceneId, int width, int height, std::vector<GLenum> formats, bool attachDepthBuffer = false, bool addStencil = false);
			};
		}
	}
}

#endif