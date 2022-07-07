#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();//引用定义在客户端中的函数，此函数声明在core.h中

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EG_CORE_WARN("Initialized Log!");
	EG_INFO("hello!");

	auto app = Engine::CreateApplication();
	app->run();
	delete app;
	
}

#endif