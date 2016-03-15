#include "ColorPicking.h"


namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			ColorPicking::ColorPicking()
				: m_mousePosition(glm::vec2(0.0f, 0.0f))
			{
				m_mouseMoveHandler = new EventHandler<ColorPicking, OnMouseMove>(this);
			}

			ColorPicking::~ColorPicking()
			{
				SAFE_DELETE(m_mouseMoveHandler);
			}

			glm::vec4 ColorPicking::GetColorByIndex(int index)
			{
				int r = index & 0xFF;
				int g = (index >> 8) & 0xFF;
				int b = (index >> 16) & 0xFF;
				return glm::vec4(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, 1.0f);
			}

			int ColorPicking::GetIndexByColor(int r, int g, int b)
			{
				return (r) | (g << 8) | (b << 16);
			}

			int ColorPicking::GetIndexOnMousePosition()
			{
				GLubyte pixel[4];
				glReadPixels(int(m_mousePosition.x), int(m_mousePosition.y), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
				int result = GetIndexByColor(pixel[0], pixel[1], pixel[2]);

				if (result == RGB_WHITE) return -1;
				return result;
			}

			void ColorPicking::operator()(const OnMouseMove& move)
			{
				m_mousePosition = move.actualPosition;
			}
		}
	}
}