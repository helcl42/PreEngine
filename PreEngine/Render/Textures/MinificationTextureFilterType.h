#ifndef MINIFICATION_TEXTURE_FILTER_TYPE_H
#define MINIFICATION_TEXTURE_FILTER_TYPE_H

namespace PreEngine
{
	namespace Render
	{
		namespace Textures
		{
			enum MinificationTextureFilterType
			{
				TEXTURE_FILTER_MIN_NEAREST = 0,		// Nearest criterion for minification
				TEXTURE_FILTER_MIN_BILINEAR,		// Bilinear criterion for minification
				TEXTURE_FILTER_MIN_NEAREST_MIPMAP,	// Nearest criterion for minification, but on closest mipmap
				TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
				TEXTURE_FILTER_MIN_TRILINEAR,		// Bilinear criterion for minification on two closest mipmaps, then averaged
			};
		}
	}
}

#endif