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
				ITexture* m_charTextures[256];

				int m_advX[256];
				int m_advY[256];

				int m_bearingX[256];
				int m_bearingY[256];

				int m_charWidth[256];
				int m_charHeight[256];

				int m_newLine;

				const int UNDEFINED_CHAR_REPLACEMENT = 63;

			public:
				FreeTypeFont();

				virtual ~FreeTypeFont();

			public:
				unsigned int GetTextWidth(const std::string& text, int pxSize);

				unsigned int GetTextHeight(const std::string& text, int pxSize);

				void Print(const std::string& text, int x, int y, int pxSize = -1);

				void Delete();

				void SetShaderProgram(IShaderProgram* shaderProgram);
			};
		}
	}
}

#endif
