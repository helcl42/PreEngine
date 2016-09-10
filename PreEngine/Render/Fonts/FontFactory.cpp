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

			void FontFactory::CreateChar(FreeTypeFont* font, int index, GLubyte* data)
			{
				FT_Load_Glyph(m_fontFace, FT_Get_Char_Index(m_fontFace, index), FT_LOAD_DEFAULT);

				FT_Render_Glyph(m_fontFace->glyph, FT_RENDER_MODE_NORMAL);
				FT_Bitmap* pBitmap = &m_fontFace->glyph->bitmap;

				int bitmapWidth = pBitmap->width;
				int bitmaptHeight = pBitmap->rows;

				// Some characters when rendered, are somehow just bigger than our desired pixel size
				// In this case, I just ignore them - another solution is to set iOneCharSquareSize in LoadFont function
				// to twice the size (just multiply by 2 and you're safe)
				if (bitmapWidth > m_oneCharSquareSize) return;
				if (bitmaptHeight > m_oneCharSquareSize) return;

				int iRow = (index%CHARS_PER_TEXTURE) / CHARS_PER_TEXTUREROOT;
				int iCol = (index%CHARS_PER_TEXTURE) % CHARS_PER_TEXTUREROOT;
				int iOneTextureByteRowSize = CHARS_PER_TEXTUREROOT * m_oneCharSquareSize;

				// Copy glyph data
				for (int channel = 0; channel < bitmaptHeight; channel++)
				{
					memcpy(data + iRow*iOneTextureByteRowSize * m_oneCharSquareSize + iCol * m_oneCharSquareSize + channel*iOneTextureByteRowSize, pBitmap->buffer + (bitmaptHeight - channel - 1)*bitmapWidth, bitmapWidth);
				}

				// Calculate glyph data
				font->m_advancesX[index] = m_fontFace->glyph->advance.x >> 6;
				font->m_bearingsX[index] = m_fontFace->glyph->metrics.horiBearingX >> 6;
				font->m_charWidths[index] = m_fontFace->glyph->metrics.width >> 6;

				font->m_advancesY[index] = (m_fontFace->glyph->metrics.height - m_fontFace->glyph->metrics.horiBearingY) >> 6;
				font->m_bearingsY[index] = m_fontFace->glyph->metrics.horiBearingY >> 6;
				font->m_charHeights[index] = m_fontFace->glyph->metrics.height >> 6;

				font->m_newLine = std::max(font->m_newLine, int(m_fontFace->glyph->metrics.height >> 6));

				glm::vec2 vQuad[] =
				{
					glm::vec2(0.0f, float(-font->m_advancesY[index] + m_oneCharSquareSize)),
					glm::vec2(0.0f, float(-font->m_advancesY[index])),
					glm::vec2(float(m_oneCharSquareSize), float(-font->m_advancesY[index] + m_oneCharSquareSize)),
					glm::vec2(float(m_oneCharSquareSize), float(-font->m_advancesY[index]))
				};

				float fOneStep = 1.0f / (float(CHARS_PER_TEXTUREROOT));
				// Texture coordinates change depending on character index, which determines its position in the texture
				glm::vec2 vTexQuad[] =
				{
					glm::vec2(float(iCol)*fOneStep, float(iRow + 1)*fOneStep),
					glm::vec2(float(iCol)*fOneStep, float(iRow)*fOneStep),
					glm::vec2(float(iCol + 1)*fOneStep, float(iRow + 1)*fOneStep),
					glm::vec2(float(iCol + 1)*fOneStep, float(iRow)*fOneStep)
				};

				// Add this char to VBO
				for(unsigned int i = 0; i < 4; i++)
				{
					font->m_vbo->AddData(&vQuad[i], sizeof(glm::vec2));
					font->m_vbo->AddData(&vTexQuad[i], sizeof(glm::vec2));
				}
			}

			inline int FontFactory::GetNextHigherPowerOfTwo(int n)
			{
				int result = 1;
				while (result < n) result <<= 1;
				return result;
			}

			IFont* FontFactory::CreateFreeTypeFont(const std::string& filePath, int pxSize, int maxCharSupport)
			{
				FreeTypeFont* font = new FreeTypeFont();

				FT_Error error = FT_Init_FreeType(&m_fontLib);
				if (error) throw FontException("Could not init FreeType library.");

				error = FT_New_Face(m_fontLib, filePath.c_str(), 0, &m_fontFace);
				if (error) throw FontException("Could not create new FreeType font face.");

				FT_Set_Pixel_Sizes(m_fontFace, pxSize, pxSize);

				font->m_loadedPixelSize = pxSize;
				m_oneCharSquareSize = GetNextHigherPowerOfTwo(pxSize);

				// Neat trick - we need to calculate ceil(iMaxCharSupport/CHARS_PER_TEXTURE) and that calculation does it, more in article
				int iNumTextures = (maxCharSupport + CHARS_PER_TEXTURE - 1) / CHARS_PER_TEXTURE;

				// One texture will store up to CHARS_PER_TEXTURE characters
				GLubyte** bTextureData = new GLubyte*[iNumTextures];

				font->m_charGroupTextures.resize(iNumTextures);

				for(int i = 0; i < iNumTextures; i++)
				{
					int iTextureDataSize = m_oneCharSquareSize * m_oneCharSquareSize * CHARS_PER_TEXTURE;
					bTextureData[i] = new GLubyte[iTextureDataSize];
					memset(bTextureData[i], 0, iTextureDataSize);
				}

				font->m_advancesX.resize(maxCharSupport); 
				font->m_advancesY.resize(maxCharSupport);
				font->m_bearingsX.resize(maxCharSupport); 
				font->m_bearingsY.resize(maxCharSupport);
				font->m_charWidths.resize(maxCharSupport); 
				font->m_charHeights.resize(maxCharSupport);

				glGenVertexArrays(1, &(font->m_vertexAttributeObject));
				glBindVertexArray(font->m_vertexAttributeObject);

				font->m_vbo->Create();
				font->m_vbo->Bind();

				for (int i = 0; i < maxCharSupport; i++) CreateChar(font, i, bTextureData[i / CHARS_PER_TEXTURE]);

				FT_Done_Face(m_fontFace);
				FT_Done_FreeType(m_fontLib);

				for(int i = 0; i < iNumTextures; i++)
				{
					ITexture* texture = m_textureFactory->CreateTexture(bTextureData[i], m_oneCharSquareSize * CHARS_PER_TEXTUREROOT, m_oneCharSquareSize * CHARS_PER_TEXTUREROOT, 8, GL_RED, false);					
					texture->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR);
					texture->SetSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					texture->SetSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					font->m_charGroupTextures[i] = texture;
				}

				font->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, 0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, (void*)(sizeof(glm::vec2)));

				for (int i = 0; i < iNumTextures; i++) SAFE_DELETE_ARRAY(bTextureData[i]);
				SAFE_DELETE_ARRAY(bTextureData);

				font->m_initialized = true;

				return font;
			}
		}
	}
}
