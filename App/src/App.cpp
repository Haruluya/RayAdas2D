#include "RApch.h"
#include "RayAdas.h"

class SandBox : public RayAdas::Application
{
public:
	SandBox();
	~SandBox();

private:

};

SandBox::SandBox()
{
	//PushLayer(new SuiXin::ImGuiLayer());
}

SandBox::~SandBox()
{

}


RayAdas::Application* RayAdas::CreateApplication()
{
	return new SandBox();
}