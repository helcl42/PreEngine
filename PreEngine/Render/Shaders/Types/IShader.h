#ifndef ISHADER_H
#define ISHADER_H

#include "../../../Core/Common.h"
#include "ShaderType.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				class IShader
				{
				public:
					virtual void Prepare() = 0;

					virtual void PrepareFromSource(const char* sourceContent) = 0;

					virtual ShaderType GetType() const = 0;

					virtual GLuint GetHandle() const = 0;

					virtual void DeleteShader() = 0;

				public:
					virtual ~IShader() {}
				};
			}
		}
	}
}

#endif