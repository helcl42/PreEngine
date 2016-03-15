#include "AbstractLight.h"


namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			AbstractLight::AbstractLight(glm::vec3 color)
				: m_color(color)
			{
			}

			AbstractLight::~AbstractLight()
			{
			}

			void AbstractLight::SetColor(glm::vec3 color)
			{
				m_color = color;
			}

			glm::vec3 AbstractLight::GetColor() const
			{
				return m_color;
			}
		}
	}
}