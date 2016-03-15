#ifndef PARTICLE_SYSTEM_TRANSFORM_FEEDBACK_H
#define PARTICLE_SYSTEM_TRANSFORM_FEEDBACK_H

#include "../../Core/Common.h"
#include "../../Render/Shaders/ShaderProgram.h"
#include "../../Render/Shaders/ShaderProgramBuilder.h"
#include "../../Render/SceneNode.h"

#include "Particle.h"
#include "ParticlesException.h"
#include "ParticleType.h"
#include "ParticleSystemTransformFeedbackSettings.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Particles
		{
			using namespace PreEngine::Utils::Render;

			class ParticleSystemTransformFeedback
			{
			private:
				bool m_isInitialized;

				unsigned int m_transformFeedbackBuffer;

				unsigned int m_particleBuffers[2];

				unsigned int m_vertexArrayObjects[2];

				unsigned int m_query;

				unsigned int m_texture;

				unsigned int m_currentReadBuffer;

				int m_numberOfParticles;

				glm::mat4 m_projection;

				glm::mat4 m_view;

				glm::vec3 m_quad1, m_quad2;

				float m_elapsedTime;

				IShaderProgram* m_updateParticlesProgram;

				IShaderProgram* m_renderParticlesProgram;

				std::vector<std::string> m_updateShaderPaths;

				std::string m_updateShaderBinaryPath;

				std::vector<std::string> m_renderShaderPaths;

				std::string m_renderShaderBinaryPath;

				ParticleSystemTransformFeedbackSettings m_settings;


				const unsigned int NUM_PARTICLE_ATTRIBUTES = 6;

				const int TOTAL_MAX_PARTICLES_COUNT = 100000;


			public:
				ParticleSystemTransformFeedback();

				virtual ~ParticleSystemTransformFeedback();

			private:
				void InitShaders();

				float GenerateRandom(float min, float add);

			public:
				void SetUpdateShaderPaths(std::vector<std::string> shaderPahts, std::string binaryPath);

				void SetRenderShaderPaths(std::vector<std::string> shaderPahts, std::string binaryPath);

				void Init();

				void Update(float deltaTime);

				void PreRender();

				void Render();

				void PostRender();

				void RenderNormals();

				void ShutDown();

				void UpdateSettings(ParticleSystemTransformFeedbackSettings settings);

				void UpdateProjectionMatrix(glm::mat4 projectionMatrix);

				void UpdateViewer(glm::vec3 eye, glm::vec3 view, glm::vec3 up);

				int GetNumberOfParticles() const;
			};
		}
	}
}

#endif