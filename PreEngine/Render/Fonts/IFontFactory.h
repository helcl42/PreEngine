#ifndef IFONT_FACTORY_H
#define IFONT_FACTORY_H

#include "../../Core/Common.h"
#include "FreeTypeFont/FreeTypeFont.h"
#include "SimpleFont/SimpleFont.h"
#include "FontException.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			class IFontFactory
			{
			public:
				virtual IFont* CreateFreeTypeFont(const std::string& filePath, int pxSize) = 0;

				virtual IFont* CreateSimpleFontFromTexture(const std::string& filePath, int pxSize, int rows, int colums) = 0;

			public:
				virtual ~IFontFactory() {}
			};
		}
	}
}

#endif