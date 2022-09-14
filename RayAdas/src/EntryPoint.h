extern RayAdas::Application* RayAdas::CreateApplication();



int main(int argc, char** argv)
{
	// 初始化日志配置。
	RayAdas::Log::Init();
	RA_CORE_INFO("LOG INIT!");
	auto app = RayAdas::CreateApplication();
	app->Run();
	delete app;	
}