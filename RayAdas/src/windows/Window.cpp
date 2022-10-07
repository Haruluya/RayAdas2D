#include "RApch.h"
#include "Window.h"

#include "windows/WinWindow.h"

namespace RayAdas
{
	URef<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

}