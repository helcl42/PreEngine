#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class ComputeShader : public AbstractShader
				{
				public:
					ComputeShader();

					ComputeShader(std::string filePath);

					virtual ~ComputeShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif