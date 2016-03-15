#ifndef SHADER_PRGRAM_STATE_H
#define SHADER_PRGRAM_STATE_H

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			enum ShaderProgramStatus
			{
				NOT_CREATED = 0,
				CREATED = 1,
				LINKED = 2,
				VALIDATED = 4,
				IN_USE = 8
			};
		}
	}
}

#endif