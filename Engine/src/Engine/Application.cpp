#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Engine {

	Application::Application() 
	{
	}

	Application::~Application() 
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			EG_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			EG_TRACE(e);
		}

		while (true);
	}

}
