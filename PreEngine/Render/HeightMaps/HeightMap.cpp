#include "HeightMap.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			HeightMap::HeightMap()
				: m_isLoaded(false), m_rows(0), m_cols(0), m_renderScale(glm::vec3(1.0f, 1.0f, 1.0f)), m_vertexAttributeObject(0)
			{
				m_vbo = new VertexBufferObject();
				m_vboIndices = new VertexBufferObject();
				m_shaderFactory = new ShaderFactory();
			}

			HeightMap::~HeightMap()
			{
				SAFE_DELETE(m_shaderFactory);
				SAFE_DELETE(m_grassProgram);
				SAFE_DELETE(m_program);
				SAFE_DELETE(m_vboGrass);
				SAFE_DELETE(m_vboIndices);
				SAFE_DELETE(m_vbo);
			}

			void HeightMap::DeleteGrass()
			{
				if (m_vboGrass != NULL)
				{
					m_vboGrass->Delete();
					SAFE_DELETE(m_vboGrass);
				}
				glDeleteVertexArrays(1, &m_grassVertexAttributeObject);
				m_grassVertexAttributeObject = 0;
			}

			void HeightMap::GenerateGrass()
			{
				DeleteGrass();

				m_vboGrass = new VertexBufferObject();
				m_vboGrass->Create();

				const float minGrassPatchOffset = 1.5f;
				const float maxGrassPatchOffset = 2.5f;
				const float grassPatchHeight = 5.0f;

				glm::vec3 currentPatchPosition(-m_renderScale.x * 0.5f + minGrassPatchOffset, 0.0f, m_renderScale.z * 0.5f - minGrassPatchOffset);

				m_countOfGrassTraingles = 0;
				while (currentPatchPosition.x < m_renderScale.x * 0.5f)
				{
					currentPatchPosition.z = m_renderScale.z * 0.5f - minGrassPatchOffset;

					while (currentPatchPosition.z > -m_renderScale.z * 0.5f)
					{
						currentPatchPosition.y = GetHeightFromRealVector(currentPatchPosition) - 0.3f;
						if (currentPatchPosition.y <= m_renderScale.y * m_maxGrassLevel && currentPatchPosition.y >= m_renderScale.y * m_minGrassLevel)
						{
							m_vboGrass->AddData(&currentPatchPosition, sizeof(glm::vec3));

							m_countOfGrassTraingles++;
						}

						currentPatchPosition.z -= minGrassPatchOffset + (maxGrassPatchOffset - minGrassPatchOffset) * float(rand() % 1000) * 0.001f;
					}
					currentPatchPosition.x += minGrassPatchOffset + (maxGrassPatchOffset - minGrassPatchOffset) * float(rand() % 1000) * 0.001f;
				}

				if (m_countOfGrassTraingles > 0)
				{
					glGenVertexArrays(1, &m_grassVertexAttributeObject);
					glBindVertexArray(m_grassVertexAttributeObject);
					m_vboGrass->Bind();
					m_vboGrass->UploadDataToGPU(GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

					glBindVertexArray(0);
				}
			}

			bool HeightMap::IsLoaded() const
			{
				return m_isLoaded;
			}

			void HeightMap::SetRenderScale(float renderX, float renderY, float renderZ)
			{
				m_renderScale = glm::vec3(renderX, renderY, renderZ);
				if (m_hasGrass) GenerateGrass();
			}

			void HeightMap::SetRenderScale(float quadSize, float height)
			{
				m_renderScale = glm::vec3(float(m_cols) * quadSize, height, float(m_rows) * quadSize);
				if (m_hasGrass) GenerateGrass();
			}

			unsigned int HeightMap::GetCountOfRows() const
			{
				return m_rows;
			}

			unsigned int HeightMap::GetCountOfColumns() const
			{
				return m_cols;
			}

			void HeightMap::SetHasGrass(bool has)
			{
				m_hasGrass = has;
				if (m_hasGrass) GenerateGrass();
			}

			bool HeightMap::HasGrass() const
			{
				return m_hasGrass;
			}

			float HeightMap::GetHeightFromRealVector(glm::vec3 position) const
			{
				unsigned int column = int((position.x + m_renderScale.x * 0.5f) * float(m_cols) / (m_renderScale.x));
				unsigned int row = int((position.z + m_renderScale.z * 0.5f) * float(m_rows) / (m_renderScale.z));

				column = std::min(column, m_cols - 1);
				row = std::min(row, m_rows - 1);

				column = std::max(column, (unsigned int)0);
				row = std::max(row, (unsigned int)0);

				return m_vertexData[row][column].y * m_renderScale.y;
			}

			void HeightMap::Init()
			{
			}

			void HeightMap::Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				m_elasedTime += deltaTime;
			}

			void HeightMap::Render()
			{
				m_program->Use();
				m_program->SetUniform("renderHeight", m_renderScale.y);
				m_program->SetUniform("maxTextureU", float(m_cols) * 0.1f);
				m_program->SetUniform("maxTextureV", float(m_rows) * 0.1f);

				m_program->SetUniform("heightMapScaleMatrix", GetScaleMatrix());

				glBindVertexArray(m_vertexAttributeObject);
				glEnable(GL_PRIMITIVE_RESTART);
				glPrimitiveRestartIndex(m_rows * m_cols);

				int numberOfIndices = (m_rows - 1) * m_cols * 2 + m_rows - 1;
				glDrawElements(GL_TRIANGLE_STRIP, numberOfIndices, GL_UNSIGNED_INT, 0);

				glDisable(GL_PRIMITIVE_RESTART);
			}

			void HeightMap::RenderGrass()
			{
				if (m_hasGrass)
				{
					m_grassProgram->Use();
					m_grassProgram->SetUniform("timeElapsed", m_elasedTime);

					glEnable(GL_MULTISAMPLE);
					glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

					glBindVertexArray(m_grassVertexAttributeObject);
					glDrawArrays(GL_POINTS, 0, m_countOfGrassTraingles);

					glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
					glDisable(GL_MULTISAMPLE);
				}
			}

			void HeightMap::RenderNormals()
			{
				glBindVertexArray(m_vertexAttributeObject);
				glEnable(GL_PRIMITIVE_RESTART);
				glPrimitiveRestartIndex(m_rows * m_cols);

				int numberOfIndices = (m_rows - 1) * m_cols * 2 + m_rows - 1;
				glDrawElements(GL_POINTS, numberOfIndices, GL_UNSIGNED_INT, 0);

				glDisable(GL_PRIMITIVE_RESTART);
			}

			void HeightMap::ShutDown()
			{
				m_grassProgram->Delete();
				m_grassProgram->DeleteShaders();

				m_program->Delete();
				m_program->DeleteShaders();

				if (!m_isLoaded) return;

				m_vbo->Delete();
				m_vboIndices->Delete();

				glDeleteVertexArrays(1, &m_vertexAttributeObject);
				glDeleteVertexArrays(1, &m_grassVertexAttributeObject);

				m_isLoaded = false;
			}

			glm::mat4 HeightMap::GetScaleMatrix() const
			{
				return glm::scale(glm::mat4(1.0f), glm::vec3(m_renderScale));
			}

			IShaderProgram* HeightMap::GetShaderProgram() const
			{
				return m_program;
			}

			void HeightMap::SetShaderProgram(IShaderProgram* program)
			{
				m_program = program;
			}

			IShaderProgram* HeightMap::GetGrassShaderProgram() const
			{
				return m_grassProgram;
			}

			void HeightMap::SetGrassShaderProgram(IShaderProgram* program)
			{
				m_grassProgram = program;
			}

			void HeightMap::SetMinGrassLevel(float minLevel)
			{
				m_minGrassLevel = minLevel;
				if (m_hasGrass) GenerateGrass();
			}

			float HeightMap::GetMinGrassLevel() const
			{
				return m_minGrassLevel;
			}

			void HeightMap::SetMaxGrassLevel(float maxLevel)
			{
				m_maxGrassLevel = maxLevel;
				if (m_hasGrass) GenerateGrass();
			}

			float HeightMap::GetMaxGrassLevel() const
			{
				return m_maxGrassLevel;
			}
		}
	}
}
