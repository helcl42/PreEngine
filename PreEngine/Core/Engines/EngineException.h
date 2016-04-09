#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include "../Common.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			using namespace PreEngine::Utils::Log;

			class EngineException : public std::runtime_error
			{
			public:
				EngineException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~EngineException()
				{
				}
			};
		}
	}
}

#endif