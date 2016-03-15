#include "Material.h"


namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			Material::Material()
				: Material(1.0f, 32.0f)
			{
			}

			Material::Material(float specIntensity, float specPower)
				: m_specularIntesity(specIntensity), m_specularPower(specPower)
			{
			}

			Material::~Material()
			{
			}

			void Material::SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName)
			{
				shaderProgram->SetUniform(variableName + ".specularIntensity", m_specularIntesity);
				shaderProgram->SetUniform(variableName + ".specularPower", m_specularPower);
			}

			void Material::SetSpecularIntensity(float specIntensity)
			{
				m_specularIntesity = specIntensity;
			}

			float Material::GetSpecularIntensity() const
			{
				return m_specularIntesity;
			}

			void Material::SetSpecularPower(float specPower)
			{
				m_specularPower = specPower;
			}

			float Material::GetSpecularPower() const
			{
				return m_specularPower;
			}
		}
	}
}