#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();//���ö����ڿͻ����еĺ������˺���������core.h��

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