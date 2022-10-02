#pragma once
extern RayAdas::Application* RayAdas::CreateApplication();



int main(int argc, char** argv)
{
	// 初始化日志配置。
	RayAdas::Log::Init();
	RA_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
	auto app = RayAdas::CreateApplication();
	RA_PROFILE_END_SESSION();

	RA_PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
	app->Run();
	RA_PROFILE_END_SESSION();

	RA_PROFILE_BEGIN_SESSION("Startup", "Profile-Shutdown.json");
	delete app;
	RA_PROFILE_END_SESSION();
}