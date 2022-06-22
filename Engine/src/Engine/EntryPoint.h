#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EG_CORE_WARN("Initialized Log!");
	int a = 5;
	EG_INFO("hello!,Var={0}",a);

	auto app = Engine::CreateApplication();
	app->run();
	delete app;
	
}

#endif