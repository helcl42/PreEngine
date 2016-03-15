#ifndef COLOR_PICKING_H
#define COLOR_PICKING_H

#include "../../Core/Common.h"
#include "../../Core/Events/EventHandler.h"
#include "../../Inputs/Core/Mouses/MouseEvents.h"

#define RGB_WHITE (0xFF | (0xFF << 8) | (0xFF << 16))

namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class ColorPicking
			{
			private:
				glm::vec2 m_mousePosition;

				EventHandler<ColorPicking, OnMouseMove>* m_mouseMoveHandler;

			public:
				ColorPicking();

				virtual ~ColorPicking();

			public:
				glm::vec4 GetColorByIndex(int index);

				int GetIndexByColor(int r, int g, int b);

				int GetIndexOnMousePosition();

			public:
				void operator()(const OnMouseMove& move);
			};
		}
	}
}

#endif