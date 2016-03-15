#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				enum ShaderType
				{
					VERTEX_SHADER = GL_VERTEX_SHADER,
					FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
					GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
					COMPUTE_SHADER = GL_COMPUTE_SHADER,
					TESSELATION_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
					TESSELATION_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER
				};
			}
		}
	}
}

#endif