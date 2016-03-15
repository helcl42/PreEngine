#include "Fog.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Effects
		{
			Fog::Fog()
				: Fog(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 10.0f, 75.0f, 0.04f, FogType::EXP)
			{
			}

			Fog::Fog(glm::vec4 color, float start, float end, float density, FogType type)
				: m_color(color), m_start(start), m_end(end), m_density(density), m_type(type)
			{
			}

			Fog::~Fog()
			{
			}

			void Fog::SetUniformData(IShaderProgram* shaderProgram, const std::string& fogVariableName)
			{
				shaderProgram->SetUniform(fogVariableName + ".color", m_color);
				shaderProgram->SetUniform(fogVariableName + ".start", m_start);
				shaderProgram->SetUniform(fogVariableName + ".end", m_end);
				shaderProgram->SetUniform(fogVariableName + ".density", m_density);
				shaderProgram->SetUniform(fogVariableName + ".type", m_type);
			}
		}
	}
}