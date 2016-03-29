#include "FragmentShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				FragmentShader::FragmentShader()
					: AbstractShader()
				{
				}

				FragmentShader::FragmentShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				FragmentShader::~FragmentShader()
				{
				}

				GLuint FragmentShader::Create()
				{
					m_handle = glCreateShader(ShaderType::FRAGMENT_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw ShaderProgramException("Error creating Fragment Shader.");
					}
					return m_handle;
				}

				ShaderType FragmentShader::GetType() const
				{
					return ShaderType::FRAGMENT_SHADER;
				}
			}
		}
	}
}