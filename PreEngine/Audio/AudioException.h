#ifndef AUDIO_EXCEPTION_H
#define AUDIO_EXCEPTION_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Audio
	{
		using namespace PreEngine::Utils::Log;

		class AudioException : public std::runtime_error
		{
		public:
			AudioException(const std::string& message)
				: std::runtime_error(message)
			{
				Logger::GetInstance().Error() << message;
			}

			virtual ~AudioException()
			{
			}
		};
	}
}

#endif