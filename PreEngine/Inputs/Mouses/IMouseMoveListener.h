#ifndef IMOUSE_MOVE_LISTENER_H
#define IMOUSE_MOVE_LISTENER_H

namespace PreEngine
{
	namespace Inputs
	{
		namespace Mouses
		{
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class IMouseMoveListener
			{
			public:
				virtual void OnMouseMoveHandler(const OnMouseMove& move) = 0;

			public:
				virtual ~IMouseMoveListener() {}
			};
		}
	}
}

#endif