#include "SpotLight.h"


namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			SpotLigth::SpotLigth()
				: SpotLigth(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 1, 20.0f, 0.1f, 0.02f, 0.0001f)
			{
			}

			SpotLigth::SpotLigth(glm::vec3 color, glm::vec3 position, glm::vec3 direction, int on, float coneAngle, float constAtt, float linearAtt, float expAtt)
				: AbstractLight(color), m_position(position), m_direction(direction), m_isOn(on), m_coneAngle(coneAngle), m_constantAttenuation(constAtt), m_linearAttenuation(linearAtt), m_expAttenuation(expAtt)
			{
			}

			SpotLigth::~SpotLigth()
			{
			}

			void SpotLigth::SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName)
			{
				shaderProgram->SetUniform(variableName + ".color", m_color);
				shaderProgram->SetUniform(variableName + ".position", m_position);
				shaderProgram->SetUniform(variableName + ".direction", m_direction);

				shaderProgram->SetUniform(variableName + ".isOn", m_isOn);
				shaderProgram->SetUniform(variableName + ".coneAngle", m_coneAngle);
				shaderProgram->SetUniform(variableName + ".coneCosine", std::cosf(glm::radians(m_coneAngle)));
				shaderProgram->SetUniform(variableName + ".constantAttenuation", m_constantAttenuation);
				shaderProgram->SetUniform(variableName + ".linearAttenuation", m_linearAttenuation);
				shaderProgram->SetUniform(variableName + ".expAttenuation", m_expAttenuation);
			}

			void SpotLigth::SetPosition(glm::vec3 position)
			{
				m_position = position;
			}

			glm::vec3 SpotLigth::GetPosition() const
			{
				return m_position;
			}

			void SpotLigth::SetDirection(glm::vec3 direction)
			{
				m_direction = direction;
			}

			glm::vec3 SpotLigth::GetDirection() const
			{
				return m_direction;
			}

			void SpotLigth::SetConstantAttenuation(float attenuation)
			{
				m_constantAttenuation = attenuation;
			}

			float SpotLigth::GetConstantAttenuation() const
			{
				return m_constantAttenuation;
			}

			void SpotLigth::SetLinearAttenuation(float attenuation)
			{
				m_linearAttenuation = attenuation;
			}

			float SpotLigth::GetLinearAttenuation() const
			{
				return m_linearAttenuation;
			}

			void SpotLigth::SetExponentialAttenuation(float attenuation)
			{
				m_expAttenuation = attenuation;
			}

			float SpotLigth::GetExponentialAttenuation() const
			{
				return m_expAttenuation;
			}
		}
	}
}