#include "GeometryShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				GeometryShader::GeometryShader()
					: AbstractShader()
				{
				}

				GeometryShader::GeometryShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				GeometryShader::~GeometryShader()
				{
				}

				GLuint GeometryShader::Create()
				{
					m_handle = glCreateShader(ShaderType::GEOMETRY_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw ShaderProgramException("Error creating Geometry Shader.");
					}
					return m_handle;
				}

				ShaderType GeometryShader::GetType() const
				{
					return ShaderType::GEOMETRY_SHADER;
				}
			}
		}
	}
}