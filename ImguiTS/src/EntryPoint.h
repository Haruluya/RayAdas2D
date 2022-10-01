#pragma once
#include "log/log.h"
#include "Application.h"

int main(int argc, char** argv)
{
	// 初始化日志配置。
	ImguiCp::Log::Init();
	IC_CORE_INFO("LOG INIT!");
	ImguiCp::Application* app = new ImguiCp::Application();
	app->runWindow();
	delete app;
}

