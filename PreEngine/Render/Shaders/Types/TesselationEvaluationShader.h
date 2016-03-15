#ifndef TESSELATION_EVALUATION_SHADER_H
#define TESSELATION_EVALUATION_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class TesselationEvaluationShader : public AbstractShader
				{
				public:
					TesselationEvaluationShader();

					TesselationEvaluationShader(std::string filePath);

					virtual ~TesselationEvaluationShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif