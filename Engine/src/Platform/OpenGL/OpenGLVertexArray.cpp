#include "egpch.h"
#include "OpenGLvertexArray.h"

#include "glad/glad.h"

namespace Engine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		EG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Engine::OpenGLVertexArray::OpenGLVertexArray()
	{
		EG_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	Engine::OpenGLVertexArray::~OpenGLVertexArray()
	{
		EG_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void Engine::OpenGLVertexArray::Bind() const
	{
		EG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void Engine::OpenGLVertexArray::UnBind() const
	{
		EG_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void Engine::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		EG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		EG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),"Vertex Buffer has no layout")

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);//存在强制类型转换
			++index;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void Engine::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		EG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}