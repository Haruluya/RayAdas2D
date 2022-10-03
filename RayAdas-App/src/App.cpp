#include <RayAdas.h>
#include "Main.h"

#include "AppTest.h"
#include "AppLayer.h"

namespace RayAdasApp {
	class App : public RayAdas::Application
	{
	public:
		App()
		{
			PushLayer(new AppTest());
		}

		~App()
		{
		}
	};
}

RayAdas::Application* RayAdas::CreateApplication()
{
	return new RayAdasApp::App();
}