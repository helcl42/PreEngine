#ifndef CORE_MESSAGES_H
#define CORE_MESSAGES_H

#include "BaseEvent.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Events
		{
			struct OnEnginePreInit : BaseEvent
			{
				OnEnginePreInit() {}

				virtual ~OnEnginePreInit() {}
			};

			struct OnEnginePostInit : BaseEvent
			{
				OnEnginePostInit() {}

				virtual ~OnEnginePostInit() {}
			};

			struct OnEngineMainLoopStart : BaseEvent
			{
				OnEngineMainLoopStart() {}

				virtual ~OnEngineMainLoopStart() {}
			};

			struct OnEngineMainLoopFinish : BaseEvent
			{
				OnEngineMainLoopFinish() {}

				virtual ~OnEngineMainLoopFinish() {}
			};

			struct OnEnginePreShutDown : BaseEvent
			{
				OnEnginePreShutDown() {}

				virtual ~OnEnginePreShutDown() {}
			};

			struct OnEnginePostShutDown : BaseEvent
			{
				OnEnginePostShutDown() {}

				virtual ~OnEnginePostShutDown() {}
			};

			struct OnEngineShutDownRequest : BaseEvent
			{
				OnEngineShutDownRequest() {}

				virtual ~OnEngineShutDownRequest() {}
			};
		}
	}
}

#endif