#ifndef PARTICLES_EXCEPTION_H
#define PARTICLES_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Particles
		{
			using namespace PreEngine::Utils::Log;

			class ParticlesException : std::runtime_error
			{
			public:
				ParticlesException(const std::string& message)
					: std::runtime_error(message)
				{
					Logger::GetInstance().Error() << message;
				}

				virtual ~ParticlesException()
				{
				}
			};
		}
	}
}

#endif