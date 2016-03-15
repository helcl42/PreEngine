#include "DirectionalLight.h"


namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			DirectionalLight::DirectionalLight()
				: DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), 0.25f, 0)
			{
			}

			DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction, float ambientIntensity, bool useAmbientOnly)
				: AbstractLight(color), m_direction(direction), m_ambientIntensity(ambientIntensity), m_useAmbientOnly(useAmbientOnly)
			{
			}

			DirectionalLight::~DirectionalLight()
			{
			}

			void DirectionalLight::SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName)
			{
				shaderProgram->SetUniform(variableName + ".color", m_color);
				shaderProgram->SetUniform(variableName + ".direction", m_direction);
				shaderProgram->SetUniform(variableName + ".ambientIntensity", m_ambientIntensity);
				shaderProgram->SetUniform(variableName + ".useAmbientOnly", m_useAmbientOnly);
			}

			void DirectionalLight::UpdateDirectionX(float div)
			{
				m_direction.x += div;
			}

			void DirectionalLight::UpdateDirectionY(float div)
			{
				m_direction.y += div;
			}

			void DirectionalLight::UpdateDirectionZ(float div)
			{
				m_direction.z += div;
			}

			void DirectionalLight::SetDirection(glm::vec3 direction)
			{
				m_direction = direction;
			}

			glm::vec3 DirectionalLight::GetDirection() const
			{
				return m_direction;
			}

			void DirectionalLight::SetAmbientIntensity(float intensity)
			{
				m_ambientIntensity = intensity;
			}

			float DirectionalLight::GetAmbientIntensity() const
			{
				return m_ambientIntensity;
			}

			void DirectionalLight::SetUseAmbientOnly(bool val)
			{
				m_useAmbientOnly = val;
			}

			bool DirectionalLight::IsUsedAmbientOnly() const
			{
				return m_useAmbientOnly;
			}
		}
	}
}