#ifndef MOUSE_MESSAGES_H
#define MOUSE_MESSAGES_H

#include "../../../Core/Common.h"
#include "../../../Core/Events/BaseEvent.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Mouses
			{
				namespace Events
				{
					using namespace PreEngine::Core::Events;

					struct OnMouseButtonPress : BaseEvent
					{
						int button;

						glm::dvec2 actualPosition;

						glm::dvec2 windowMeasures;

						int modifiers;


						OnMouseButtonPress() {}

						OnMouseButtonPress(int button, glm::dvec2 actualPosition, int modifiers)
							: button(button), actualPosition(actualPosition), modifiers(modifiers) {}

						virtual ~OnMouseButtonPress() {}
					};

					struct OnMouseButtonRelease : BaseEvent
					{
						int button;

						glm::dvec2 actualPosition;

						glm::dvec2 windowMeasures;

						int modifiers;


						OnMouseButtonRelease() {}

						OnMouseButtonRelease(int button, glm::dvec2 actualPosition, int modifiers)
							: button(button), actualPosition(actualPosition), modifiers(modifiers) {}

						virtual ~OnMouseButtonRelease() {}
					};

					struct OnMouseMove : BaseEvent
					{
						glm::dvec2 actualPosition;

						glm::dvec2 previousPosition;

						glm::dvec2 diff;

						glm::dvec2 windowMeasures;


						OnMouseMove() {}

						OnMouseMove(glm::vec2 actual, glm::vec2 prev, glm::vec2 diff, glm::dvec2 windowMeasures)
							: actualPosition(actual), previousPosition(prev), diff(diff), windowMeasures(windowMeasures) {}

						virtual ~OnMouseMove() {}
					};

					struct OnMouseScroll : BaseEvent
					{
						glm::dvec2 diff;


						OnMouseScroll() {}

						OnMouseScroll(glm::vec2 diff)
							: diff(diff) {}

						virtual ~OnMouseScroll() {}
					};
				}
			}
		}
	}
}

#endif