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


			private:
				void CreateChar(FreeTypeFont* font, int index);

				inline int GetNextHigherPowerOfTwo(int n);

			public:
				FontFactory();

				virtual ~FontFactory();

			public:
				IFont* CreateFreeTypeFont(const std::string& filePath, int pxSize);

				IFont* CreateSimpleFontFromTexture(const std::string& filePath, int pxSize, int rows, int colums);
			};
		}
	}
}

#endif