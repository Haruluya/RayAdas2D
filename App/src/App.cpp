#include "RayAdas.h"

class App :public RayAdas::Application
{
public:
	App() {
	}

	~App()
		{}


};

RayAdas::Application* RayAdas::CreateApplication()
{
	return new App();
};