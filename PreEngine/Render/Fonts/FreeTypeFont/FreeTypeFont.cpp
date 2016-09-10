#include "FreeTypeFont.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			FreeTypeFont::FreeTypeFont()
			{
			}

			FreeTypeFont::~FreeTypeFont()
			{
				for (auto& texture : m_charGroupTextures)
				{
					SAFE_DELETE(texture);
				}
			}

			unsigned int FreeTypeFont::GetTextWidth(const std::string& inputText, int pxSize)
			{
				std::string text(inputText);
				std::vector<std::string> lines;
				StringUtils::Split(text, '\n', lines);
				if (lines.size() > 0)
				{
					std::string longestLine = lines[0];
					for (unsigned int i = 1; i < lines.size(); i++)
					{
						if (longestLine.length() < lines[i].length()) longestLine = lines[i];
					}
					text = longestLine;
				}

				unsigned int result = 0;
				for (unsigned int i = 0; i < text.size(); i++)
				{
					result += m_advancesX[text[i]];
				}

				return result * pxSize / m_loadedPixelSize;
			}

			unsigned int FreeTypeFont::GetTextHeight(const std::string& text, int pxSize)
			{
				unsigned int linesCount = 0;
				for (unsigned int i = 0; i < text.size(); i++)
				{
					if (text[i] == '\n') linesCount++;
				}

				return m_advancesY['A'] * linesCount * pxSize / m_loadedPixelSize;
			}

			void FreeTypeFont::Print(const std::string& text, int x, int y, int pxSize)
			{				
				glBindVertexArray(m_vertexAttributeObject);

				m_program->SetUniform("gSampler", 0);

				glDisable(GL_DEPTH_TEST);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				int curX = x;
				int curY = y;
				if (pxSize == -1) pxSize = m_loadedPixelSize;
				float scale = float(pxSize) / float(m_loadedPixelSize);
				int lastBoundTextureIndex = -1;

				for (unsigned int i = 0; i < text.size(); i++)
				{
					if (text[i] == '\n')
					{
						curX = x;
						curY -= m_newLine * pxSize / m_loadedPixelSize;
						continue;
					}

					int index = int(text[i]);
					if (index < 0 || index >= 128)
					{
						index = UNDEFINED_CHAR_REPLACEMENT;
					}

					int iTextureNeeded = index / CHARS_PER_TEXTURE;
					if (iTextureNeeded != lastBoundTextureIndex)
					{
						lastBoundTextureIndex = iTextureNeeded;
						m_charGroupTextures[iTextureNeeded]->Bind(0);
					}

					curX += m_bearingsX[index] * pxSize / m_loadedPixelSize;

					if (text[i] != ' ')
					{
						glm::mat4 modelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(curX), float(curY), 0.0f));
						modelView = glm::scale(modelView, glm::vec3(scale));
						m_program->SetUniform("modelViewMatrix", modelView);
						glDrawArrays(GL_TRIANGLE_STRIP, index * 4, 4);
					}

					curX += (m_advancesX[index] - m_bearingsX[index]) * pxSize / m_loadedPixelSize;
				}

				glDisable(GL_BLEND);

				glEnable(GL_DEPTH_TEST);
			}

			void FreeTypeFont::Print(const std::wstring& text, int x, int y, int pxSize)
			{				
				glBindVertexArray(m_vertexAttributeObject);

				m_program->SetUniform("gSampler", 0);

				glDisable(GL_DEPTH_TEST);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				int curX = x;
				int curY = y;
				if (pxSize == -1) pxSize = m_loadedPixelSize;
				float scale = float(pxSize) / float(m_loadedPixelSize);
				int lastBoundTextureIndex = -1;

				for (unsigned int i = 0; i < text.size(); i++)
				{
					if (text[i] == '\n')
					{
						curX = x;
						curY -= m_newLine * pxSize / m_loadedPixelSize;
						continue;
					}

					int index = int(text[i]);
					if (index < 0 || index >= 128)
					{
						index = UNDEFINED_CHAR_REPLACEMENT;
					}

					int iTextureNeeded = index / CHARS_PER_TEXTURE;
					if (iTextureNeeded != lastBoundTextureIndex)
					{
						lastBoundTextureIndex = iTextureNeeded;
						m_charGroupTextures[iTextureNeeded]->Bind(0);
					}

					curX += m_bearingsX[index] * pxSize / m_loadedPixelSize;

					if (text[i] != ' ')
					{
						glm::mat4 modelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(curX), float(curY), 0.0f));
						modelView = glm::scale(modelView, glm::vec3(scale));
						m_program->SetUniform("modelViewMatrix", modelView);
						glDrawArrays(GL_TRIANGLE_STRIP, index * 4, 4);
					}

					curX += (m_advancesX[index] - m_bearingsX[index]) * pxSize / m_loadedPixelSize;
				}

				glDisable(GL_BLEND);

				glEnable(GL_DEPTH_TEST);
			}

			void FreeTypeFont::Delete()
			{
				for (auto& texture : m_charGroupTextures)
				{
					texture->Delete();
				}

				m_vbo->Delete();
				glDeleteVertexArrays(1, &m_vertexAttributeObject);
			}

			void FreeTypeFont::SetShaderProgram(IShaderProgram* shaderProgram)
			{
				m_program = shaderProgram;
			}
		}
	}
}