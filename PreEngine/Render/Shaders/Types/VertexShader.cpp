#include "VertexShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				VertexShader::VertexShader()
					: AbstractShader()
				{
				}

				VertexShader::VertexShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				VertexShader::~VertexShader()
				{
				}

				GLuint VertexShader::Create()
				{
					m_handle = glCreateShader(ShaderType::VERTEX_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw ShaderProgramException("Error creating Vertex Shader.");
					}
					return m_handle;
				}

				ShaderType VertexShader::GetType() const
				{
					return ShaderType::VERTEX_SHADER;
				}
			}
		}
	}
}