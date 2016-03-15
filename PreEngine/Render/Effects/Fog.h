#ifndef FOG_H
#define FOG_H

#include "../../Core/Common.h"
#include "../../Render/Shaders/ShaderProgram.h"

#include "FogType.h"
#include "IEffect.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Effects
		{
			using namespace PreEngine::Render::Shaders;

			class Fog : public IEffect
			{
			public:
				glm::vec4 m_color;

				float m_start;

				float m_end;

				float m_density;

				FogType m_type;

			public:
				Fog();

				Fog(glm::vec4 color, float start, float end, float density, FogType type);

				virtual ~Fog();

			public:
				void SetUniformData(IShaderProgram* shaderProgram, const std::string& fogVariableName);
			};
		}
	}
}

#endif