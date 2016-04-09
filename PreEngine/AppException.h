#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include "Core/Common.h"

namespace PreEngine
{
	using namespace PreEngine::Utils::Log;

	class AppException : std::runtime_error
	{
	public:
		AppException(const std::string& message)
			: std::runtime_error(message)
		{
		}

		virtual ~AppException()
		{
		}
	};
}

#endif