#include "MD2Model.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				AnimationData MD2Model::animlist[MAX_ANIMATIONS] =
				{
					// first, last, fps
					{ 0, 39, 9 },		// STAND
					{ 40, 45, 10 },		// RUN
					{ 46, 53, 10 },		// ATTACK
					{ 54, 57, 7 },		// PAIN_A
					{ 58, 61, 7 },		// PAIN_B
					{ 62, 65, 7 },		// PAIN_C
					{ 66, 71, 7 },		// JUMP
					{ 72, 83, 7 },		// FLIP
					{ 84, 94, 7 },		// SALUTE
					{ 95, 111, 10 },	// FALLBACK
					{ 112, 122, 7 },	// WAVE
					{ 123, 134, 6 },	// POINT
					{ 135, 153, 10 },	// CROUCH_STAND
					{ 154, 159, 7 },	// CROUCH_WALK
					{ 160, 168, 10 },	// CROUCH_ATTACK
					{ 196, 172, 7 },	// CROUCH_PAIN
					{ 173, 177, 5 },	// CROUCH_DEATH
					{ 178, 183, 7 },	// DEATH_FALLBACK
					{ 184, 189, 7 },	// DEATH_FALLFORWARD
					{ 190, 197, 7 },	// DEATH_FALLBACKSLOW
					{ 198, 198, 5 },	// BOOM
				};

				MD2Model::MD2Model()
					: m_defaultTexturesEnabled(true)
				{
					m_animationProgram = new ShaderProgram();
				}

				MD2Model::~MD2Model()
				{
					SAFE_DELETE(m_vboTextureCoords);
					SAFE_DELETE(m_animationProgram);
					SAFE_DELETE(m_texture);

					for (auto vbo : m_vboFrameVertices)
					{
						SAFE_DELETE(vbo);
					}
				}

				void MD2Model::SetShaderProgram(IShaderProgram* program)
				{
					m_animationProgram = program;
				}

				IShaderProgram* MD2Model::GetShaderProgram() const
				{
					return m_animationProgram;
				}

				void MD2Model::Init()
				{
				}

				void MD2Model::ShutDown()
				{					
					m_texture->Delete();
					m_vboTextureCoords->Delete();

					for (auto vbo : m_vboFrameVertices)	vbo->Delete();					
				}

				void MD2Model::Render(AnimationState* animState)
				{
					glBindVertexArray(m_vertexArrayObject);

					int totalOffset = 0;
					
					if(m_defaultTexturesEnabled) m_texture->Bind();

					if (animState == NULL)
					{
						glEnableVertexAttribArray(0);
						m_vboFrameVertices[0]->Bind();
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

						m_animationProgram->SetUniform("interpolation", -1.0f);

						for (unsigned int i = 0; i < m_renderModes.size(); i++)
						{
							glDrawArrays(m_renderModes[i], totalOffset, m_numberOfRenderedVertices[i]);
							totalOffset += m_numberOfRenderedVertices[i];
						}
					}
					else
					{
						glEnableVertexAttribArray(0);
						m_vboFrameVertices[animState->curr_frame]->Bind();
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

						glEnableVertexAttribArray(3);
						m_vboFrameVertices[animState->next_frame]->Bind();
						glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

						glEnableVertexAttribArray(2);
						m_vboFrameVertices[animState->curr_frame]->Bind();
						glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

						glEnableVertexAttribArray(4);
						m_vboFrameVertices[animState->next_frame]->Bind();
						glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

						m_animationProgram->SetUniform("interpolation", animState->interpol);

						for (unsigned int i = 0; i < m_renderModes.size(); i++)
						{
							glDrawArrays(m_renderModes[i], totalOffset, m_numberOfRenderedVertices[i]);
							totalOffset += m_numberOfRenderedVertices[i];
						}
					}

					glBindVertexArray(0);
				}

				void MD2Model::UpdateAnimation(AnimationState* animState, float elapsedTime)
				{
					animState->curr_time += elapsedTime;

					if (animState->curr_time - animState->old_time > (1.0f / float(animState->fps)))
					{
						animState->old_time = animState->curr_time;
						animState->curr_frame = animState->next_frame;
						animState->next_frame++;

						// loop animation
						if (animState->next_frame > animState->endframe) animState->next_frame = animState->startframe;
					}

					animState->interpol = float(animState->fps) * (animState->curr_time - animState->old_time);
				}

				AnimationState MD2Model::StartAnimation(AnimationType type)
				{
					AnimationState res;
					res.startframe = animlist[type].first_frame;
					res.endframe = animlist[type].last_frame;
					res.curr_frame = animlist[type].first_frame;
					res.next_frame = animlist[type].first_frame + 1;

					res.fps = animlist[type].fps;
					res.type = type;

					res.curr_time = 0.0f;
					res.old_time = 0.0f;
					res.interpol = 0.0f;
					return res;
				}

				void MD2Model::PauseAnimation()
				{
					// TODO
				}

				void MD2Model::StopAnimation()
				{
					// TODO
				}

				void  MD2Model::SetDefaultTexturesEnabled(bool enabled)
				{
					m_defaultTexturesEnabled = enabled;
				}

				bool MD2Model::IsDefaultTexturesEnabled() const
				{
					return m_defaultTexturesEnabled;
				}
			}
		}
	}
}