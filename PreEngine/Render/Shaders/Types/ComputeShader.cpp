#include "ComputeShader.h"

#include "ComputeShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				ComputeShader::ComputeShader()
					: AbstractShader()
				{
				}

				ComputeShader::ComputeShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				ComputeShader::~ComputeShader()
				{
				}

				GLuint ComputeShader::Create()
				{
					m_handle = glCreateShader(ShaderType::COMPUTE_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw new ShaderProgramException("Error creating Compute Shader.");
					}
					return m_handle;
				}

				ShaderType ComputeShader::GetType() const
				{
					return ShaderType::COMPUTE_SHADER;
				}
			}
		}
	}
}