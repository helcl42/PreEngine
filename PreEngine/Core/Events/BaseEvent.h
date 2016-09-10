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
				bool alreadyHandled = false;

				BaseEvent() 
				{
				}

				virtual ~BaseEvent() 
				{
				}

				bool IsHandled() const
				{
					return alreadyHandled;
				}
			};
		}
	}
}

#endif