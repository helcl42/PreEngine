#include "TesselationControlShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				TesselationControlShader::TesselationControlShader()
					: AbstractShader()
				{
				}

				TesselationControlShader::TesselationControlShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				TesselationControlShader::~TesselationControlShader()
				{
				}

				GLuint TesselationControlShader::Create()
				{
					m_handle = glCreateShader(ShaderType::TESSELATION_CONTROL_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw ShaderProgramException("Error creating Tesselation Control Shader.");
					}
					return m_handle;
				}

				ShaderType TesselationControlShader::GetType() const
				{
					return ShaderType::TESSELATION_CONTROL_SHADER;
				}
			}
		}
	}
}