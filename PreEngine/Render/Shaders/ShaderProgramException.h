#ifndef SHADER_PROGRAM_EXCEPTION_H
#define SHADER_PROGRAM_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			using namespace Utils::Log;

			class ShaderProgramException : public std::runtime_error
			{
			public:
				ShaderProgramException(const std::string& message)
					: std::runtime_error(message)
				{
					Logger::GetInstance().Error() << message;
				}

				virtual ~ShaderProgramException()
				{
				}
			};
		}
	}
}

#endif