#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class VertexShader : public AbstractShader
				{
				public:
					VertexShader();

					VertexShader(std::string filePath);

					virtual ~VertexShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif