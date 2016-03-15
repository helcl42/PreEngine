#ifndef IWINDOW_H
#define IWINDOW_H


namespace PreEngine
{
	namespace Windows
	{
		template <class WindowType>
		class IWindow
		{
		public:
			virtual bool Init() = 0;

			virtual void ShutDown() = 0;

			virtual bool ShouldClose() const = 0;

			virtual unsigned int GetWidth() const = 0;

			virtual unsigned int GetHeight() const = 0;

			virtual bool IsInFullScreen() const = 0;

			virtual bool IsFocused() const = 0;

			virtual WindowType* GetWindow() const = 0;

			virtual void SwapBuffers() const = 0;

			virtual unsigned int GetSceneId() const = 0;

			virtual unsigned int GetWindowPosition() const = 0;

			virtual void RefreshWindow() = 0;

			virtual void MoveWindow(MoveDirection direction) = 0;

			virtual void MakeWindowContextMain() = 0;

			virtual void RegisterChildWindow(IWindow<WindowType>* child) = 0;

		public:
			virtual ~IWindow() {}
		};
	}
}

#endif