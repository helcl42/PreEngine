#ifndef GL_WINDOW_EXCEPTION_H
#define GL_WINDOW_EXCEPTION_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Windows
	{
		using namespace PreEngine::Utils::Log;

		class GLWindowException : public std::runtime_error
		{
		public:
			GLWindowException(const std::string& message)
				: std::runtime_error(message)
			{
				Logger::GetInstance().Error() << message;
			}

			virtual ~GLWindowException()
			{
			}
		};
	}
}

#endif