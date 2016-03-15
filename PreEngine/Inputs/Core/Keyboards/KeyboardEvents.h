#ifndef KEYBOARD_MESSAGES_H
#define KEYBOARD_MESSAGES_H

#include "../../../Core/Events/BaseEvent.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			namespace Keyboards
			{
				namespace Events
				{
					using namespace PreEngine::Core::Events;

					struct OnKeyPress : BaseEvent
					{
						int key;

						int modifiers;

						OnKeyPress() {}

						OnKeyPress(int key, int modifiers)
							: key(key), modifiers(modifiers) {}

						virtual ~OnKeyPress() {}
					};

					struct OnKeyRelease : BaseEvent
					{
						int key;

						int modifiers;

						OnKeyRelease() {}

						OnKeyRelease(int key, int modifiers)
							: key(key), modifiers(modifiers) {}

						virtual ~OnKeyRelease() {}
					};
				}
			}
		}
	}
}

#endif