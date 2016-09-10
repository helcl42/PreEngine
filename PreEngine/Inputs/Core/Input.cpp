#include "Input.h"

namespace PreEngine
{
	namespace Inputs
	{
		namespace Core
		{
			Input::Input()
			{
				m_createHandler = new EventHandler<Input, OnCreate>(this);
				m_closeHandler = new EventHandler<Input, OnClose>(this);
			}

			Input::~Input()
			{
				SAFE_DELETE(m_closeHandler);
				SAFE_DELETE(m_createHandler);
			}

			bool Input::Init()
			{
				return true;
			}

			void Input::Update(float deltaTime)
			{
				m_mouseInput->Update(deltaTime);
				m_keyboardInput->Update(deltaTime);
			}

			void Input::ShutDown()
			{
			}

			void Input::operator()(const OnCreate& created)
			{
				if (m_mouseInput == NULL) m_mouseInput = new MouseInput(created.window);
				if (m_keyboardInput == NULL) m_keyboardInput = new KeyboardInput(created.window);

				m_mouseInput->Init();
				m_keyboardInput->Init();
			}

			void Input::operator()(const OnClose& closed)
			{				
				SAFE_DELETE(m_keyboardInput);
				SAFE_DELETE(m_mouseInput);
			}

			MouseInput* Input::GetMouseInput() const
			{
				return m_mouseInput;
			}

			KeyboardInput* Input::GetKeyboardInput() const
			{
				return m_keyboardInput;
			}
		}
	}
}