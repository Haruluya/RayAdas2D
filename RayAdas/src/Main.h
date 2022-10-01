extern RayAdas::Application* RayAdas::CreateApplication();



int main(int argc, char** argv)
{
	// 初始化日志配置。
	RayAdas::Log::Init();
	auto app = RayAdas::CreateApplication();
	app->Run();
	delete app;	
}