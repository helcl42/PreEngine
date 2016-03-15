#ifndef TESSELATION_CONTROL_SHADER_H
#define TESSELATION_CONTROL_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class TesselationControlShader : public AbstractShader
				{
				public:
					TesselationControlShader();

					TesselationControlShader(std::string filePath);

					virtual ~TesselationControlShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif