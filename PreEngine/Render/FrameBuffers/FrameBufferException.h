#ifndef FRAME_BUFFER_EXCEPTION_H
#define FRAME_BUFFER_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace FrameBuffers
		{
			using namespace PreEngine::Utils::Log;

			class FrameBufferException : public std::runtime_error
			{
			public:
				FrameBufferException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~FrameBufferException()
				{
				}
			};
		}
	}
}

#endif