#ifndef IMOUSE_BUTTON_LISTENER_H
#define IMOUSE_BUTTON_LISTENER_H


#include "../Core/Mouses/MouseEvents.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Mouses
		{
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class IMouseButtonListener
			{
			public:
				virtual void OnMouseButtonPressedHandler(const OnMouseButtonPress& press) = 0;

				virtual void OnMouseButtonReleasedHandler(const OnMouseButtonRelease& release) = 0;

			public:
				virtual ~IMouseButtonListener() {}
			};
		}
	}
}

#endif