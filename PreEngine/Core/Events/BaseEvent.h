#ifndef BASE_MESSAGE_H
#define BASE_MESSAGE_H

namespace PreEngine
{
	namespace Core
	{
		namespace Events
		{
			struct BaseEvent
			{
				BaseEvent() {}

				virtual ~BaseEvent() {}
			};
		}
	}
}

#endif