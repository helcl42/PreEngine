#ifndef ILIGHT_H
#define ILIGHT_H

#include "../Shaders/ShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			using namespace PreEngine::Render::Shaders;

			class ILight
			{
			public:
				virtual void SetColor(glm::vec3 color) = 0;

				virtual glm::vec3 GetColor() const = 0;

				virtual void SetUniformData(IShaderProgram* shaderProgram, const std::string& variableName) = 0;

			public:
				virtual ~ILight() {}
			};
		}
	}
}

#endif