#ifndef PARTICLE_SYSTEM_TRANSFORM_FEEDBACK_SETTINGS_H
#define PARTICLE_SYSTEM_TRANSFORM_FEEDBACK_SETTINGS_H

namespace PreEngine
{
	namespace Render
	{
		namespace Particles
		{
			struct ParticleSystemTransformFeedbackSettings
			{
				glm::vec3 genPosition;

				glm::vec3 genVelocityMin;

				glm::vec3 genVelocityMax;

				glm::vec3 genGravity;

				glm::vec3 genColor;

				float genLifeMin;

				float genLifeMax;

				float genSize;

				float nextGenerationTime;

				int numberToGenerate;
			};
		}
	}
}

#endif