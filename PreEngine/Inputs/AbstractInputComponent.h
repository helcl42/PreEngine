#ifndef ABSTRACT_INPUT_COMPONENT_H
#define ABSTRACT_INPUT_COMPONENT_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Inputs
	{
		class AbstractInputComponent
		{
		protected:
			std::mutex m_mutex;

		public:
			AbstractInputComponent();

			virtual ~AbstractInputComponent();
		};
	}
}

#endif
