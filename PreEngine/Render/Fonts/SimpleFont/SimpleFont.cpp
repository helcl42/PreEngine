#include "SimpleFont.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			SimpleFont::SimpleFont()
			{
			}

			SimpleFont::~SimpleFont()
			{
				SAFE_DELETE(m_fontTexture);
			}

			unsigned int SimpleFont::PrepareData(const std::string& text, int x, int y, int size)
			{
				int baseX = x;
				unsigned int countOfVertices = 0;
				for (unsigned int i = 0; i < text.size(); i++)
				{
					char character = text[i];
					float uv_x = (character % m_colums) / float(m_colums);
					float uv_y = (character / m_rows) / float(m_rows);

					if (character == '\n') // TODO newLine + space character
					{
						x = baseX;
						y -= size;
					}

					glm::vec2 vertex_up_left = glm::vec2(x + i * size, y + size);
					glm::vec2 vertex_up_right = glm::vec2(x + i * size + size, y + size);
					glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
					glm::vec2 vertex_down_left = glm::vec2(x + i * size, y);

					glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
					glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / float(m_colums), uv_y);
					glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / float(m_colums), uv_y + 1.0f / float(m_rows));
					glm::vec2 uv_down_left = glm::vec2(uv_x, uv_y + 1.0f / float(m_rows));

					m_vbo->AddData(&vertex_up_left, sizeof(glm::vec2));
					m_vbo->AddData(&uv_up_left, sizeof(glm::vec2));

					m_vbo->AddData(&vertex_down_left, sizeof(glm::vec2));
					m_vbo->AddData(&uv_down_left, sizeof(glm::vec2));

					m_vbo->AddData(&vertex_up_right, sizeof(glm::vec2));
					m_vbo->AddData(&uv_up_right, sizeof(glm::vec2));

					m_vbo->AddData(&vertex_down_right, sizeof(glm::vec2));
					m_vbo->AddData(&uv_down_right, sizeof(glm::vec2));

					m_vbo->AddData(&vertex_up_right, sizeof(glm::vec2));
					m_vbo->AddData(&uv_up_right, sizeof(glm::vec2));

					m_vbo->AddData(&vertex_down_left, sizeof(glm::vec2));
					m_vbo->AddData(&uv_down_left, sizeof(glm::vec2));

					countOfVertices += 6;
				}
				return countOfVertices;
			}

			unsigned int SimpleFont::GetTextWidth(const std::string& text, int pxSize)
			{
				throw FontException("Not implemented!");
			}

			unsigned int SimpleFont::GetTextHeight(const std::string& text, int pxSize)
			{
				throw FontException("Not implemented!");
			}

			void SimpleFont::Print(const std::string& text, int x, int y, int size)
			{
				unsigned int countOfVertices = PrepareData(text, x, y, size);

				glBindVertexArray(m_vertexAttributeObject);

				m_vbo->Bind();
				m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

				m_program->Use();
				m_program->SetUniform("gSampler", 0);
				m_fontTexture->Bind();

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec2), 0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec2), (void*)sizeof(glm::vec2));

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glDrawArrays(GL_TRIANGLES, 0, countOfVertices);

				glDisable(GL_BLEND);
			}

			void SimpleFont::Delete()
			{
				m_vbo->Delete();
				m_fontTexture->Delete();

				glDeleteVertexArrays(1, &m_vertexAttributeObject);
			}

			void SimpleFont::SetShaderProgram(IShaderProgram* shaderProgram)
			{
				m_program = shaderProgram;
			}
		}
	}
}