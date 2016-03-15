#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class FragmentShader : public AbstractShader
				{
				public:
					FragmentShader();

					FragmentShader(std::string filePath);

					virtual ~FragmentShader();

				public:
					GLuint Create();

					ShaderType GetType() const;
				};
			}
		}
	}
}

#endif