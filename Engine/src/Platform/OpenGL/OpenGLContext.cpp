#include "egpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		EG_CORE_ASSERT(m_WindowHandle, "Failed to initialize GLAD");
	}

	void OpenGLContext::Init()
	{
		EG_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_CORE_ASSERT(status, "Failed to initialize GLAD");

		EG_CORE_INFO("OpenGL info:");
		EG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		EG_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}