#include "egpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Engine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}