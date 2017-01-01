#ifndef IFRAME_BUFFER_FACTORY_H
#define IFRAME_BUFFER_FACTORY_H

#include "IFrameBuffer.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			class IFrameBufferFactory
			{
			public:
				virtual IFrameBuffer* CreateFrameBuffer(int sceneId, int width, int height, std::vector<GLenum> formats, bool attachDepthBuffer = false, bool addStencil = false) = 0;

			public:
				virtual ~IFrameBufferFactory() {}
			};
		}
	}
}

#endif