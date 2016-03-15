#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "AbstractLight.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			class PointLight : public AbstractLight
			{
			private:
				glm::vec3 m_position;

				float m_ambientIntensity;

				float m_constantAttenuation;

				float m_linearAttenuation;

				float m_expAttenuation;

			public:
				PointLight();

				PointLight(glm::vec3 color, glm::vec3 position, float ambientIntensity, float constAtt, float linearAtt, float expAtt);

				virtual ~PointLight();

			public:
				void SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName);

			public:
				void SetPosition(glm::vec3 position);

				glm::vec3 GetPosition() const;

				void SetAmbientIntensity(float intensity);

				float GetAmbientIntensity() const;

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