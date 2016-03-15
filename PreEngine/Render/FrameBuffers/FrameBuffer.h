#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "../../Core/Events/EventHandler.h"
#include "../../Windows/WindowEvents.h"
#include "../../Utils/Render/RenderUtil.h"

#include "../Textures/Texture.h"
#include "../Frustums/ViewFrustumEvents.h"

#include "FrameBufferException.h"
#include "IFrameBuffer.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			using namespace PreEngine;
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Render::Textures;
			using namespace PreEngine::Utils::Render;		

			class FrameBuffer : public IFrameBuffer
			{
			private:
				friend class FrameBufferFactory;

			private:
				static std::map<unsigned int, std::stack<IFrameBuffer*> > s_customDefaultFrameBuffers;

				static std::map<unsigned int, GLuint> s_boundFrameBufferHandles;

			private:
				unsigned int m_sceneId;

				unsigned int m_width;

				unsigned int m_height;

				bool m_hasDepthBufferAttached;

				GLuint m_frameBufferHandle;

				GLuint m_depthRenderBufferHandle;

				std::vector<ITexture*> m_frameBufferTextures;

				EventHandler<FrameBuffer, Windows::Events::OnResize>* m_resizeHandler;

			public:
				FrameBuffer(unsigned int sceneId = 0);

				virtual ~FrameBuffer();

			public:
				void Create();

				bool AddDepthBuffer();

				bool HasDepthBufferAttached() const;

				void Bind(bool setFullViewport = true);

				void Delete();

				void SetFramebufferTextureFiltering(enum MagnificationTextureFilterType magnification, enum MinificationTextureFilterType minification);

				void BindFrameBufferTexture(int textureIndex = 0, int textureUnit = 0, bool regenerateMipMaps = false);

				unsigned int GetWidth() const;

				unsigned int GetHeight() const;

				ITexture* GetTexture(int textureIndex = 0) const;

				GLuint GetHandle() const;

			private:
				static void BindFrameBuffer(unsigned int sceneId, GLuint frameBufferHandle);

			public:
				static void BindDefaultFrameBuffer(unsigned int sceneId, int width, int height);

				static void SetCustomDefaultFrameBuffer(unsigned int sceneId, IFrameBuffer* customDefaultFrameBuffer);

				static IFrameBuffer* GetCurrentDefaultFrameBuffer(unsigned int sceneId);

			public:
				void operator() (const Windows::Events::OnResize& resize);
			};
		}
	}
}

#endif