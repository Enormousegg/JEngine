#include "egpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		EG_CORE_ASSERT(false, "RendererAPI:None is currently not support!"); break;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}
		EG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}