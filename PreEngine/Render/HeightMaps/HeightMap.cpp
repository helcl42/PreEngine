#include "HeightMap.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			HeightMap::HeightMap()
				: m_isLoaded(false), m_rows(0), m_cols(0), m_renderScale(glm::vec3(0.0f, 0.0f, 0.0f)), m_vertexAttributeObject(0)
			{
				m_vbo = new VertexBufferObject();
				m_vboIndices = new VertexBufferObject();
				m_shaderFactory = new ShaderFactory();
			}

			HeightMap::~HeightMap()
			{
				SAFE_DELETE(m_shaderFactory);
				SAFE_DELETE(m_program);
				SAFE_DELETE(m_vboIndices);
				SAFE_DELETE(m_vbo);
			}

			bool HeightMap::IsLoaded() const
			{
				return m_isLoaded;
			}

			void HeightMap::SetRenderScale(float renderX, float renderY, float renderZ)
			{
				m_renderScale = glm::vec3(renderX, renderY, renderZ);
			}

			void HeightMap::SetRenderScale(float quadSize, float height)
			{
				m_renderScale = glm::vec3(float(m_cols) * quadSize, height, float(m_rows) * quadSize);
			}

			unsigned int HeightMap::GetCountOfRows() const
			{
				return m_rows;
			}

			unsigned int HeightMap::GetCountOfColumns() const
			{
				return m_cols;
			}

			float HeightMap::GetHeightFromRealVector(glm::vec3 position) const
			{
				unsigned int column = int((position.x + m_renderScale.x * 0.5f)*float(m_cols) / (m_renderScale.x));
				unsigned int row = int((position.z + m_renderScale.z * 0.5f)*float(m_rows) / (m_renderScale.z));

				column = std::min(column, m_cols - 1);
				row = std::min(row, m_rows - 1);

				column = std::max(column, (unsigned int)0);
				row = std::max(row, (unsigned int)0);

				return m_vertexData[row][column].y * m_renderScale.y;
			}

			void HeightMap::Init()
			{
				m_program = new ShaderProgram();
				m_program->Create();
				m_program->AddShader(m_shaderFactory->CreateVertexShader(".//Data//Shaders//Ch21_terrain.vert.hlsl"));
				m_program->AddShader(m_shaderFactory->CreateFragmentShader(".//Data//Shaders//Ch21_terrain.frag.hlsl"));
				m_program->Link();
				/*m_program->Link(false);

				for (int i = 0; i < 5; i++)
				{
					std::stringstream ss;
					ss << "gSampler[" << i << "]";
					m_program->SetUniform(ss.str(), i);
				}

				m_program->SetUniform("gShadowMap", 6);
				m_program->Validate();*/
			}

			void HeightMap::Update(float deltaTime)
			{
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
			}

			void HeightMap::RenderNormals()
			{
				glBindVertexArray(m_vertexAttributeObject);
				glEnable(GL_PRIMITIVE_RESTART);
				glPrimitiveRestartIndex(m_rows * m_cols);

				int numberOfIndices = (m_rows - 1) * m_cols * 2 + m_rows - 1;
				glDrawElements(GL_POINTS, numberOfIndices, GL_UNSIGNED_INT, 0);
			}

			void HeightMap::ShutDown()
			{
				m_program->Delete();
				m_program->DeleteShaders();

				if (!m_isLoaded) return;

				m_vbo->Delete();
				m_vboIndices->Delete();

				glDeleteVertexArrays(1, &m_vertexAttributeObject);
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
		}
	}
}
