#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "AbstractLight.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			class SpotLigth : public AbstractLight
			{
			private:				
				glm::vec3 m_position;

				glm::vec3 m_direction;

				int m_isOn;

				float m_coneAngle;

				float m_constantAttenuation;

				float m_linearAttenuation;

				float m_expAttenuation;

			public:
				SpotLigth();

				SpotLigth(glm::vec3 color, glm::vec3 position, glm::vec3 direction, int on, float coneAngle, float constAtt, float linearAtt, float expAtt);

				virtual ~SpotLigth();

			public:
				void SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName);

			public:
				void SetPosition(glm::vec3 position);

				glm::vec3 GetPosition() const;

				void SetDirection(glm::vec3 direction);

				glm::vec3 GetDirection() const;

				void SetOn(bool on);

				bool IsOn() const;

				void SetConstantAttenuation(float attenuation);

				float GetConstantAttenuation() const;

				void SetLinearAttenuation(float attenuation);

				float GetLinearAttenuation() const;

				void SetExponentialAttenuation(float attenuation);

				float GetExponentialAttenuation() const;
			};
		}
	}
}

#endif
