#include "PointLight.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			PointLight::PointLight()
				: PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.3f, 0.007f, 0.00008f)
			{
			}

			PointLight::PointLight(glm::vec3 color, glm::vec3 position, float ambientIntensity, float constAtt, float linearAtt, float expAtt)
				: AbstractLight(color), m_position(position), m_ambientIntensity(ambientIntensity), m_constantAttenuation(constAtt), m_linearAttenuation(linearAtt), m_expAttenuation(expAtt)
			{
			}

			PointLight::~PointLight()
			{
			}

			void PointLight::SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName)
			{
				shaderProgram->SetUniform(variableName + ".color", m_color);
				shaderProgram->SetUniform(variableName + ".position", m_position);
				shaderProgram->SetUniform(variableName + ".ambientIntensity", m_ambientIntensity);
				shaderProgram->SetUniform(variableName + ".constantAttenuation", m_constantAttenuation);
				shaderProgram->SetUniform(variableName + ".linearAttenuation", m_linearAttenuation);
				shaderProgram->SetUniform(variableName + ".expAttenuation", m_expAttenuation);
			}

			void PointLight::SetPosition(glm::vec3 position)
			{
				m_position = position;
			}

			glm::vec3 PointLight::GetPosition() const
			{
				return m_position;
			}

			void PointLight::SetAmbientIntensity(float intensity)
			{
				m_ambientIntensity = intensity;
			}

			float PointLight::GetAmbientIntensity() const
			{
				return m_ambientIntensity;
			}

			void PointLight::SetConstantAttenuation(float attenuation)
			{
				m_constantAttenuation = attenuation;
			}

			float PointLight::GetConstantAttenuation() const
			{
				return m_constantAttenuation;
			}

			void PointLight::SetLinearAttenuation(float attenuation)
			{
				m_linearAttenuation = attenuation;
			}

			float PointLight::GetLinearAttenuation() const
			{
				return m_linearAttenuation;
			}

			void PointLight::SetExponentialAttenuation(float attenuation)
			{
				m_expAttenuation = attenuation;
			}

			float PointLight::GetExponentialAttenuation() const
			{
				return m_expAttenuation;
			}
		}
	}
}