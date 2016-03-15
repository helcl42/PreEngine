#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../Core/Common.h"
#include "../../Render/Shaders/ShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			using namespace PreEngine::Render::Shaders;

			class Material
			{
			private:
				float m_specularIntesity;

				float m_specularPower;

			public:
				Material();

				Material(float specIntensity, float specPower);

				virtual ~Material();

			public:
				void SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName);

			public:
				void SetSpecularIntensity(float specIntensity);

				float GetSpecularIntensity() const;

				void SetSpecularPower(float specPower);

				float GetSpecularPower() const;
			};
		}
	}
}

#endif