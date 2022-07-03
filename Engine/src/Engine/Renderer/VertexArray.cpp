#include "egpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		EG_CORE_ASSERT(false, "RendererAPI:None is currently not support!"); break;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}
		EG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}