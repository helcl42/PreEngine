#include "ParticleSystemTransformFeedback.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Particles
		{
			ParticleSystemTransformFeedback::ParticleSystemTransformFeedback()
				: m_isInitialized(false), m_currentReadBuffer(0)
			{
			}

			ParticleSystemTransformFeedback::~ParticleSystemTransformFeedback()
			{
				SAFE_DELETE(m_renderParticlesProgram);
				SAFE_DELETE(m_updateParticlesProgram);
			}

			void ParticleSystemTransformFeedback::InitShaders()
			{
				if (m_isInitialized) return;

				// HACK !!!
				if (m_updateShaderPaths.size() < 2 || m_renderShaderPaths.size() < 3) throw new ParticlesException("Ivalid shaders paths set.");
			
				// update particles shader
				const char* shaderVariyings[] =
				{
					"positionOut",
					"velocityOut",
					"colorOut",
					"lifeTimeOut",
					"sizeOut",
					"typeOut"
				};

				ShaderProgramBuilder programBuilder;
				// update particles shader
				programBuilder.SetBinaryPath(m_updateShaderBinaryPath);
				programBuilder.AddShader(ShaderType::VERTEX_SHADER, m_updateShaderPaths[0]);
				programBuilder.AddShader(ShaderType::GEOMETRY_SHADER, m_updateShaderPaths[1]);
				m_updateParticlesProgram = programBuilder.Build(false, false);
				for (unsigned int i = 0; i < NUM_PARTICLE_ATTRIBUTES; i++)
				{
					glTransformFeedbackVaryings(m_updateParticlesProgram->GetHandle(), NUM_PARTICLE_ATTRIBUTES, shaderVariyings, GL_INTERLEAVED_ATTRIBS);
				}
				m_updateParticlesProgram->Link();
				m_updateParticlesProgram->Validate();

				// render particles shader
				programBuilder.SetBinaryPath(m_renderShaderBinaryPath);
				programBuilder.AddShader(ShaderType::VERTEX_SHADER, m_renderShaderPaths[0]);
				programBuilder.AddShader(ShaderType::GEOMETRY_SHADER, m_renderShaderPaths[1]);
				programBuilder.AddShader(ShaderType::FRAGMENT_SHADER, m_renderShaderPaths[2]);
				m_renderParticlesProgram = programBuilder.Build();
			}

			float ParticleSystemTransformFeedback::GenerateRandom(float min, float add)
			{
				float random = float(rand() % (RAND_MAX + 1)) / float(RAND_MAX);
				return min + add * random;
			}

			void ParticleSystemTransformFeedback::SetUpdateShaderPaths(std::vector<std::string> shaderPaths, std::string binaryPath)
			{
				m_updateShaderPaths = shaderPaths;
				m_updateShaderBinaryPath = binaryPath;
			}

			void ParticleSystemTransformFeedback::SetRenderShaderPaths(std::vector<std::string> shaderPaths, std::string binaryPath)
			{
				m_renderShaderPaths = shaderPaths;
				m_renderShaderBinaryPath = binaryPath;
			}

			void ParticleSystemTransformFeedback::Init()
			{
				InitShaders();

				glGenTransformFeedbacks(1, &m_transformFeedbackBuffer);
				glGenQueries(1, &m_query);

				glGenBuffers(2, m_particleBuffers);
				glGenVertexArrays(2, m_vertexArrayObjects);

				Particle initParticle;
				initParticle.type = ParticleType::GENERATOR;

				for (unsigned int i = 0; i < 2; i++)
				{
					glBindVertexArray(m_vertexArrayObjects[i]);
					glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffers[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * TOTAL_MAX_PARTICLES_COUNT, NULL, GL_DYNAMIC_DRAW);
					glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle), &initParticle);

					for (unsigned int i = 0; i < NUM_PARTICLE_ATTRIBUTES; i++)
					{
						glEnableVertexAttribArray(i);
					}

					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)0);											// position
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*) sizeof(glm::vec3));							// velocity
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)(2 * sizeof(glm::vec3)));						// color
					glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)(3 * sizeof(glm::vec3)));						// lifeTimeout
					glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)(3 * sizeof(glm::vec3) + sizeof(float)));		// size
					glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, sizeof(Particle), (const GLvoid*)(3 * sizeof(glm::vec3) + 2 * sizeof(float)));	// type
				}

				m_currentReadBuffer = 0;
				m_numberOfParticles = 1;
				m_isInitialized = true;
			}

			void ParticleSystemTransformFeedback::Update(float deltaTime)
			{
				if (!m_isInitialized) return;

				m_updateParticlesProgram->Use();
				m_updateParticlesProgram->SetUniform("deltaTime", deltaTime);
				m_updateParticlesProgram->SetUniform("genPosition", m_settings.genPosition);
				m_updateParticlesProgram->SetUniform("genVelocityMin", m_settings.genVelocityMin);
				m_updateParticlesProgram->SetUniform("genVelocityRange", m_settings.genVelocityMax - m_settings.genVelocityMin);
				m_updateParticlesProgram->SetUniform("genColor", m_settings.genColor);
				m_updateParticlesProgram->SetUniform("genGravity", m_settings.genGravity);
				m_updateParticlesProgram->SetUniform("genLifeTimeMin", m_settings.genLifeMin);
				m_updateParticlesProgram->SetUniform("genLifeTimeRange", m_settings.genLifeMax - m_settings.genLifeMin);
				m_updateParticlesProgram->SetUniform("genSize", m_settings.genSize);
				m_updateParticlesProgram->SetUniform("numberToGenerate", 0);

				m_elapsedTime += deltaTime;

				if (m_elapsedTime > m_settings.nextGenerationTime)
				{
					m_elapsedTime -= m_settings.nextGenerationTime;

					glm::vec3 randomSeed(GenerateRandom(-10.0f, 20.0f), GenerateRandom(-10.0f, 20.0f), GenerateRandom(-10.0f, 20.0f));
					m_updateParticlesProgram->SetUniform("numberToGenerate", m_settings.numberToGenerate);
					m_updateParticlesProgram->SetUniform("randomSeed", randomSeed);
				}

				glEnable(GL_RASTERIZER_DISCARD);
				glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedbackBuffer);

				glBindVertexArray(m_vertexArrayObjects[m_currentReadBuffer]);
				glEnableVertexAttribArray(1); // enable velocity

				glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffers[1 - m_currentReadBuffer]);

				glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, m_query);
				glBeginTransformFeedback(GL_POINTS);

				glDrawArrays(GL_POINTS, 0, m_numberOfParticles);

				glEndTransformFeedback();
				glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

				glGetQueryObjectiv(m_query, GL_QUERY_RESULT, &m_numberOfParticles);

				if (m_settings.numberToGenerate > TOTAL_MAX_PARTICLES_COUNT) m_settings.numberToGenerate = TOTAL_MAX_PARTICLES_COUNT;

				m_currentReadBuffer = 1 - m_currentReadBuffer;

				glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
			}

			void ParticleSystemTransformFeedback::PreRender()
			{
			}

			void ParticleSystemTransformFeedback::Render()
			{
				if (!m_isInitialized) return;

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glDepthMask(GL_FALSE);

				glDisable(GL_RASTERIZER_DISCARD);

				m_renderParticlesProgram->Use();
				m_renderParticlesProgram->SetUniform("matrices.projectionMatrix", m_projection);
				m_renderParticlesProgram->SetUniform("matrices.viewMatrix", m_view);
				m_renderParticlesProgram->SetUniform("quad1", m_quad1);
				m_renderParticlesProgram->SetUniform("quad2", m_quad2);
				m_renderParticlesProgram->SetUniform("gSampler", 0);

				glBindVertexArray(m_vertexArrayObjects[m_currentReadBuffer]);
				glDisableVertexAttribArray(1); // disable velocity, because it is not needed

				glDrawArrays(GL_POINTS, 0, m_numberOfParticles);

				glDepthMask(GL_TRUE);
				glDisable(GL_BLEND);
			}

			void ParticleSystemTransformFeedback::PostRender()
			{
			}

			void ParticleSystemTransformFeedback::RenderNormals()
			{
				if (!m_isInitialized) return;

				glDisable(GL_RASTERIZER_DISCARD);

				glBindVertexArray(m_vertexArrayObjects[m_currentReadBuffer]);
				glDisableVertexAttribArray(1); // disable velocity, because it is not needed

				glDrawArrays(GL_POINTS, 0, m_numberOfParticles);
			}

			void ParticleSystemTransformFeedback::ShutDown()
			{
				if (!m_isInitialized) return;

				m_updateParticlesProgram->Delete();
				m_updateParticlesProgram->DeleteShaders();
				SAFE_DELETE(m_updateParticlesProgram);

				m_renderParticlesProgram->Delete();
				m_renderParticlesProgram->DeleteShaders();
				SAFE_DELETE(m_renderParticlesProgram);

				glDeleteVertexArrays(2, m_vertexArrayObjects);
				glDeleteTransformFeedbacks(1, &m_transformFeedbackBuffer);
				glDeleteBuffers(2, m_particleBuffers);
				glDeleteQueries(1, &m_query);

				m_isInitialized = false;
			}

			void ParticleSystemTransformFeedback::UpdateSettings(ParticleSystemTransformFeedbackSettings settings)
			{
				m_settings = settings;
			}

			void ParticleSystemTransformFeedback::UpdateProjectionMatrix(glm::mat4 projectionMatrix)
			{
				m_projection = projectionMatrix;
			}

			void ParticleSystemTransformFeedback::UpdateViewer(glm::vec3 eye, glm::vec3 view, glm::vec3 up)
			{
				m_view = RenderUtil::GetViewMatrix(eye, view, up);
				view = glm::normalize(view - eye);
				m_quad1 = glm::cross(view, up);
				m_quad1 = glm::normalize(m_quad1);
				m_quad2 = glm::cross(view, m_quad1);
				m_quad2 = glm::normalize(m_quad2);
			}

			int ParticleSystemTransformFeedback::GetNumberOfParticles() const
			{
				return m_numberOfParticles;
			}
		}
	}
}