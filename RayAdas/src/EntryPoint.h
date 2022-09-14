extern RayAdas::Application* RayAdas::CreateApplication();

int main(int argc, char** argv)
{
	auto app = RayAdas::CreateApplication();
	app->Run();
	delete app;
}