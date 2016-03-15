#ifndef IMOUSE_SCROLL_LISTENER_H
#define IMOUSE_SCROLL_LISTENER_H

namespace PreEngine
{
	namespace Inputs
	{
		namespace Mouses
		{
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class IMouseScrollListener
			{
			public:
				virtual void OnMouseScrollHandler(const OnMouseScroll& scroll) = 0;

			public:
				virtual ~IMouseScrollListener() {}
			};
		}
	}
}

#endif