#include "egpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Engine {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		EG_CORE_ASSERT(false, "RendererAPI:None is currently not support!"); break;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}
		EG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}