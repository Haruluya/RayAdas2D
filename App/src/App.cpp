#include "RayAdas.h"

class ExampleLayer : public RayAdas::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (RayAdas::Input::IsKeyPressed(RA_KEY_TAB))
			RA_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(RayAdas::Event& event) override
	{
		if (event.GetEventType() == RayAdas::EventType::KeyPressed)
		{
			RayAdas::KeyPressedEvent& e = (RayAdas::KeyPressedEvent&)event;
			if (e.GetKeyCode() == RA_KEY_TAB)
				RA_TRACE("Tab key is pressed (event)!");
			RA_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public RayAdas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

RayAdas::Application* RayAdas::CreateApplication()
{
	return new Sandbox();
}