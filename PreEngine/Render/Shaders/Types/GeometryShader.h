#ifndef GEOMETR_SHADER_H
#define GEOMETR_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class GeometryShader : public AbstractShader
				{
				public:
					GeometryShader();

					GeometryShader(std::string filePath);

					virtual ~GeometryShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif