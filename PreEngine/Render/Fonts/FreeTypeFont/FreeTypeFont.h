#ifndef FREE_TYPE_FONT_H
#define FREE_TYPE_FONT_H

#include "../../../Core/Common.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>


#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Textures/Texture.h"
#include "../../Textures/TextureFactory.h"
#include "../../Shaders/ShaderProgram.h"
#include "../../../Utils/StringUtils.h"

#include "../AbstractFont.h"

#define CHARS_PER_TEXTURE 1024
#define CHARS_PER_TEXTUREROOT 32

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			using namespace PreEngine::Render::Textures;
			using namespace PreEngine::Utils;

			class FreeTypeFont : public AbstractFont
			{
			private:
				friend class FontFactory;

			private:
				std::vector<ITexture*> m_charGroupTextures;

				std::vector<int> m_advancesX, m_advancesY;

				std::vector<int> m_bearingsX, m_bearingsY;

				std::vector<int> m_charWidths, m_charHeights;				

				bool m_initialized;

				int m_newLine;

				const int UNDEFINED_CHAR_REPLACEMENT = '?';

			public:
				FreeTypeFont();

				virtual ~FreeTypeFont();

			public:
				unsigned int GetTextWidth(const std::string& text, int pxSize);

				unsigned int GetTextHeight(const std::string& text, int pxSize);

				void Print(const std::string& text, int x, int y, int pxSize = -1);

				void Print(const std::wstring& text, int x, int y, int pxSize = -1);

				void Delete();

				void SetShaderProgram(IShaderProgram* shaderProgram);
			};
		}
	}
}

#endif
