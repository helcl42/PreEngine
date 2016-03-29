#include "TesselationEvaluationShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				TesselationEvaluationShader::TesselationEvaluationShader()
					: AbstractShader()
				{
				}

				TesselationEvaluationShader::TesselationEvaluationShader(std::string filePath)
					: AbstractShader(filePath)
				{
				}

				TesselationEvaluationShader::~TesselationEvaluationShader()
				{
				}

				GLuint TesselationEvaluationShader::Create()
				{
					m_handle = glCreateShader(ShaderType::TESSELATION_EVALUATION_SHADER);
					if (m_handle == GL_FALSE)
					{
						throw ShaderProgramException("Error creating Tesselation Evaluation Shader.");
					}
					return m_handle;
				}

				ShaderType TesselationEvaluationShader::GetType() const
				{
					return ShaderType::TESSELATION_EVALUATION_SHADER;
				}
			}
		}
	}
}