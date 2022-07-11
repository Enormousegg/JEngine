#include "egpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Engine {

	////////////////////////////////////////////////////////////////////
	////////////////////////Vertex Buffer///////////////////////////////
	////////////////////////////////////////////////////////////////////

	Engine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		EG_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		EG_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void Engine::OpenGLVertexBuffer::Bind() const
	{
		EG_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void Engine::OpenGLVertexBuffer::UnBind() const
	{
		EG_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////////////
	////////////////////////Index Buffer////////////////////////////////
	////////////////////////////////////////////////////////////////////

	Engine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		EG_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		EG_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void Engine::OpenGLIndexBuffer::Bind() const
	{
		EG_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void Engine::OpenGLIndexBuffer::UnBind() const
	{
		EG_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

