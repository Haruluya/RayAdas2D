#pragma once


int main(int argc, char** argv);

namespace RayAdas {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}
