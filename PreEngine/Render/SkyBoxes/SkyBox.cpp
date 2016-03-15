#include "SkyBox.h"

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			SkyBox::SkyBox()
			{
				m_vbo = new VertexBufferObject();
			}

			SkyBox::~SkyBox()
			{
				for (unsigned int i = 0; i < 6; i++)
				{
					SAFE_DELETE(m_textures[i]);
				}

				SAFE_DELETE(m_vbo);
			}

			void SkyBox::Render()
			{
				glDepthMask(GL_FALSE);

				glBindVertexArray(m_vertexArrayObject);

				for (unsigned int i = 0; i < 6; i++)
				{
					m_textures[i]->Bind();
					glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
				}

				glDepthMask(GL_TRUE);
			}

			void SkyBox::Delete()
			{
				for (unsigned int i = 0; i < 6; i++)
				{
					m_textures[i]->Delete();
				}

				glDeleteVertexArrays(1, &m_vertexArrayObject);
				m_vbo->Delete();
			}
		}
	}
}