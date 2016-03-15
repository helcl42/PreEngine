#ifndef INPUT_H
#define INPUT_H

#include "../../Core/Common.h"
#include "../../Windows/GLWindow.h"
#include "../../Core/System.h"

#include "../../Core/Events/EventChannel.h"
#include "../../Core/Events/EventHandler.h"
#include "Keyboards/KeyboardEvents.h"
#include "../../Windows/WindowEvents.h"

#include "Keyboards/KeyboardInput.h"
#include "Mouses/MouseInput.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;
			using namespace PreEngine::Inputs::Core::Mouses;
			using namespace PreEngine::Inputs::Core::Keyboards;
			using namespace PreEngine::Windows::Events;
			using namespace PreEngine::Utils::Log;

			class Input : public System
			{
			private:
				MouseInput* m_mouseInput;

				KeyboardInput* m_keyboardInput;

				EventHandler<Input, OnCreate>* m_createHandler;

				EventHandler<Input, OnClose>* m_closeHandler;

			public:
				Input();

				virtual ~Input();

			public:
				bool Init();

				void Update(float deltaTime);

				void ShutDown();

			public:
				void operator()(const OnCreate& created);

				void operator()(const OnClose& closed);

			public:
				MouseInput* GetMouseInput() const;

				KeyboardInput* GetKeyboardInput() const;
			};
		}
	}
}

#endif