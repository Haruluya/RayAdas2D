#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "windows/Window.h"
#include "events/ApplicationEvent.h"

#include "layer/LayerStack.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"

#include "imgui/ImGuiLayer.h"
#include "rendering/Shader.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}
