#include "FontFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			FontFactory::FontFactory()
			{
				m_textureFactory = new TextureFactory();
			}

			FontFactory::~FontFactory()
			{
				SAFE_DELETE(m_textureFactory);
			}

			void FontFactory::CreateChar(FreeTypeFont* font, int index)
			{
				FT_Load_Glyph(m_fontFace, FT_Get_Char_Index(m_fontFace, index), FT_LOAD_DEFAULT);
				FT_Render_Glyph(m_fontFace->glyph, FT_RENDER_MODE_NORMAL);

				FT_Bitmap* bitmap = &m_fontFace->glyph->bitmap;

				unsigned int realWidth = bitmap->width;
				unsigned int realHeight = bitmap->rows;
				unsigned int newTextureWidth = GetNextHigherPowerOfTwo(realWidth);
				unsigned int newTextureHeight = GetNextHigherPowerOfTwo(realHeight);

				GLubyte* data = new GLubyte[newTextureWidth * newTextureHeight];
				for (unsigned int r = 0; r < newTextureHeight; r++)
				{
					for (unsigned int c = 0; c < newTextureWidth; c++)
					{
						data[r * newTextureWidth + c] = (r >= realHeight || c >= realWidth) ? 0 : bitmap->buffer[(realHeight - r - 1) * realWidth + c];
					}
				}

				font->m_charTextures[index] = m_textureFactory->CreateTexture(data, newTextureWidth, newTextureHeight, 8, GL_RED, false);
				font->m_charTextures[index]->SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);

				font->m_charTextures[index]->SetSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				font->m_charTextures[index]->SetSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				font->m_advX[index] = m_fontFace->glyph->advance.x >> 6;
				font->m_bearingX[index] = m_fontFace->glyph->metrics.horiBearingX >> 6;
				font->m_charWidth[index] = m_fontFace->glyph->metrics.width >> 6;

				font->m_advY[index] = (m_fontFace->glyph->metrics.height - m_fontFace->glyph->metrics.horiBearingY) >> 6;
				font->m_bearingY[index] = m_fontFace->glyph->metrics.horiBearingY >> 6;
				font->m_charHeight[index] = m_fontFace->glyph->metrics.height >> 6;

				font->m_newLine = std::max(font->m_newLine, int(m_fontFace->glyph->metrics.height >> 6));

				glm::vec2 quad[] =
				{
					glm::vec2(0.0f, float(-font->m_advY[index] + newTextureHeight)),
					glm::vec2(0.0f, float(-font->m_advY[index])),
					glm::vec2(float(newTextureWidth), float(-font->m_advY[index] + newTextureHeight)),
					glm::vec2(float(newTextureWidth), float(-font->m_advY[index]))
				};

				glm::vec2 textureQuad[] =
				{
					glm::vec2(0.0f, 1.0f),
					glm::vec2(0.0f, 0.0f),
					glm::vec2(1.0f, 1.0f),
					glm::vec2(1.0f, 0.0f)
				};

				for (unsigned int i = 0; i < 4; i++)
				{
					font->m_vbo->AddData(&quad[i], sizeof(glm::vec2));
					font->m_vbo->AddData(&textureQuad[i], sizeof(glm::vec2));
				}

				SAFE_DELETE_ARRAY(data);
			}

			inline int FontFactory::GetNextHigherPowerOfTwo(int n)
			{
				int result = 1;
				while (result < n) result <<= 1;
				return result;
			}

			IFont* FontFactory::CreateFreeTypeFont(const std::string& filePath, int pxSize)
			{
				FreeTypeFont* font = new FreeTypeFont();

				FT_Error error = FT_Init_FreeType(&m_fontLib);
				if (error) throw FontException("Could not init FreeType library.");

				error = FT_New_Face(m_fontLib, filePath.c_str(), 0, &m_fontFace);
				if (error) throw FontException("Could not create new FreeType font face.");

				FT_Set_Pixel_Sizes(m_fontFace, pxSize, pxSize);

				font->m_loadedPixelSize = pxSize;

				glGenVertexArrays(1, &(font->m_vertexAttributeObject));
				glBindVertexArray(font->m_vertexAttributeObject);

				font->m_vbo->Create();
				font->m_vbo->Bind();

				for (unsigned int i = 0; i < 128; i++) CreateChar(font, i);

				FT_Done_Face(m_fontFace);
				FT_Done_FreeType(m_fontLib);

				font->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, 0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, (void*)(sizeof(glm::vec2)));

				return font;
			}

			IFont* FontFactory::CreateSimpleFontFromTexture(const std::string& filePath, int pxSize, int rows, int colums)
			{
				SimpleFont* font = new SimpleFont();
				font->m_loadedPixelSize = pxSize;
				font->m_colums = colums;
				font->m_rows = rows;
				font->m_fontTexture = m_textureFactory->CreateTexture(filePath, true);

				glGenVertexArrays(1, &(font->m_vertexAttributeObject));
				glBindVertexArray(font->m_vertexAttributeObject);

				IVertexBufferObject* vbo = new VertexBufferObject();
				vbo->Create();
				vbo->Bind();
				font->m_vbo = vbo;

				return font;
			}
		}
	}
}
