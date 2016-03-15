#include "AbstractFont.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			AbstractFont::AbstractFont()
			{
				m_vbo = new VertexBufferObject();
			}

			AbstractFont::~AbstractFont()
			{
				SAFE_DELETE(m_vbo);
			}
		}
	}
}