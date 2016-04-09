#ifndef SCRIPTING_EXCEPTION_H
#define SCRIPTING_EXCEPTION_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Scripting
	{
		using namespace PreEngine::Utils::Log;

		class ScriptingException : public std::runtime_error
		{
		public:
			ScriptingException(const std::string& message)
				: std::runtime_error(message)
			{
			}

			virtual ~ScriptingException()
			{
			}
		};
	}
}

#endif