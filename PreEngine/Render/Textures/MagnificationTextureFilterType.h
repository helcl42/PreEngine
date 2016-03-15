#ifndef MAGNIFICATION_TEXTURE_FILTER_TYPE_H
#define MAGNIFICATION_TEXTURE_FILTER_TYPE_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			enum MagnificationTextureFilterType
			{
				TEXTURE_FILTER_MAG_NEAREST,		// Nearest criterion for magnification
				TEXTURE_FILTER_MAG_BILINEAR		// Bilinear criterion for magnification
			};
		}
	}
}

#endif