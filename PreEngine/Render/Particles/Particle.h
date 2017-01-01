#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Particles
		{
			class Particle
			{
			public:
				glm::vec3 position;

				glm::vec3 m_velocity;

				glm::vec3 color;

				float lifeTime;

				float size;

				int type;
			};
		}
	}
}

#endif