#include <RayAdas.h>
#include <Main.h>

#include "EditorLayer.h"

namespace RayAdas {

	class EditorApp : public Application
	{
	public:
		EditorApp(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "EditorApp";
		spec.CommandLineArgs = args;

		return new EditorApp(spec);
	}

}