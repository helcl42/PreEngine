#ifndef ITHREAD_H
#define ITHREAD_H

#include "../Common.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Threading
		{
			class IThread
			{
			public:
				virtual void RunThread() = 0;

				virtual bool Join(unsigned int timeout = 2000) = 0;

				virtual bool IsFinished() const = 0;

				virtual void SetFinished(bool finished) = 0;

			public:
				virtual ~IThread() {}
			};
		}
	}
}

#endif