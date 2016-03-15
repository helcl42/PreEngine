#ifndef IKEYBOARD_LISTENER_H
#define IKEYBOARD_LISTENER_H

#include "../Core/Keyboards/KeyboardEvents.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Keyboards
		{
			using namespace PreEngine::Inputs::Core::Keyboards::Events;

			class IKeyboardListener
			{
			public:
				virtual void OnKeyPressedHandler(const OnKeyPress& press) = 0;

				virtual void OnKeyReleasedHandler(const OnKeyRelease& release) = 0;

			public:
				virtual ~IKeyboardListener() {}
			};
		}
	}
}

#endif