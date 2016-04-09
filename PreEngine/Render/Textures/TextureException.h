#ifndef TEXTURE_EXCEPTION_H
#define TEXTURE_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			class TextureException : public std::runtime_error
			{
			public:
				TextureException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~TextureException()
				{
				}
			};
		}
	}
}

#endif