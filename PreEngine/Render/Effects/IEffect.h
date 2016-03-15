#ifndef IEFFECT_H
#define IEFFECT_H

#include "../../Core/Common.h"
#include "../../Render/Shaders/ShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Effects
		{
			using namespace PreEngine::Render::Shaders;

			class IEffect
			{
			public:
				virtual void SetUniformData(IShaderProgram* shaderProgram, const std::string& fogVariableName) = 0;

			public:
				virtual ~IEffect() {}
			};
		}
	}
}

#endif