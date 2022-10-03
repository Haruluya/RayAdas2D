#include <RayAdas.h>
#include <Main.h>

#include "EditorLayer.h"

namespace RayAdasEditor {

	class EditorApp : public RayAdas::Application
	{
	public:
		EditorApp()
			: RayAdas::Application("RayAdas Editor")
		{
			PushLayer(new EditorLayer());
		}

		~EditorApp()
		{
		}
	};

}
RayAdas::Application* RayAdas::CreateApplication()
{
	return new RayAdasEditor::EditorApp();
}