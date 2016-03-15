#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "AbstractLight.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			class DirectionalLight : public AbstractLight
			{
			private:
				glm::vec3 m_direction;

				float m_ambientIntensity;

				bool m_useAmbientOnly;

			public:
				DirectionalLight();

				DirectionalLight(glm::vec3 color, glm::vec3 direction, float ambientIntensity, bool useAmbientOnly = false);

				virtual ~DirectionalLight();

			public:
				void SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName);

			public:
				void SetDirection(glm::vec3 direction);

				void UpdateDirectionX(float div);

				void UpdateDirectionY(float div);

				void UpdateDirectionZ(float div);

				glm::vec3 GetDirection() const;

				void SetAmbientIntensity(float intensity);

				float GetAmbientIntensity() const;

				void SetUseAmbientOnly(bool val);

				bool IsUsedAmbientOnly() const;
			};
		}
	}
}

#endif