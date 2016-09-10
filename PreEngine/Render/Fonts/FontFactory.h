#ifndef FONT_FACTORY_H
#define FONT_FACTORY_H

#include "IFontFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			class FontFactory : public IFontFactory
			{
			private:
				FT_Library m_fontLib;

				FT_Face m_fontFace;

				ITextureFactory* m_textureFactory;

				int m_oneCharSquareSize;


			private:
				void CreateChar(FreeTypeFont* font, int index, GLubyte* bData);

				inline int GetNextHigherPowerOfTwo(int n);

			public:
				FontFactory();

				virtual ~FontFactory();

			public:
				IFont* CreateFreeTypeFont(const std::string& filePath, int pxSize, int maxCharSupport = 1024);
			};
		}
	}
}

#endif