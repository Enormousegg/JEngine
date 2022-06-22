#pragma once

#include "core.h"

namespace Engine {
	
	class EG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//定义在客户端中
	Application* CreateApplication();

}


