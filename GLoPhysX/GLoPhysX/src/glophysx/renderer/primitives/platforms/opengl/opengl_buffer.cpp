#include "gxpch.h"
#include "opengl_buffer.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERER {

		OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, uint32_t size)
		{
			glGenBuffers(1, &m_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);

			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}
		OpenglVertexBuffer::~OpenglVertexBuffer()
		{
			glDeleteBuffers(1, &m_buffer_id);
		}
		void OpenglVertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
		}
		void OpenglVertexBuffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		OpenglIndexBuffer::OpenglIndexBuffer(uint32_t* indices, uint32_t size) : m_count(size)
		{
			glGenBuffers(1, &m_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		}
		OpenglIndexBuffer::~OpenglIndexBuffer()
		{
			glDeleteBuffers(1, &m_buffer_id);
		}
		void OpenglIndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
		}
		void OpenglIndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
