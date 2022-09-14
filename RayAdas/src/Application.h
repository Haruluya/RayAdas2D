#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "windows/Window.h"
#include "events/ApplicationEvent.h"

#include "layer/LayerStack.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
int main(int argc, char** argv);

namespace RayAdas {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}
