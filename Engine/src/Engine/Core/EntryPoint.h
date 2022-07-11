#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();//引用定义在客户端中的函数，此函数声明在core.h中

int main(int argc, char** argv)
{
	Engine::Log::Init();

	EG_PROFILE_BEGIN_SESSION("Startup", "JEngineProfile-Startup.json");
	auto app = Engine::CreateApplication();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Runtime", "JEngineProfile-Runtime.json");
	app->run();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Shutdown", "JEngineProfile-Shutdown.json");
	delete app;
	EG_PROFILE_END_SESSION();

}

#endif