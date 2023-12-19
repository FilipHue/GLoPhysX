#include "gxpch.h"
#include "opengl_buffer.h"

#include "glad/glad.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace RENDERING {

		// VERTEX BUFFER

		OpenglVertexBuffer::OpenglVertexBuffer(uint32_t size)
		{
			GLOP_PROFILE_FUNCTION();

			glGenBuffers(1, &m_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);

			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		}

		OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, uint32_t size)
		{
			GLOP_PROFILE_FUNCTION();

			glGenBuffers(1, &m_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);

			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}
		OpenglVertexBuffer::~OpenglVertexBuffer()
		{
			GLOP_PROFILE_FUNCTION();

			glDeleteBuffers(1, &m_buffer_id);
		}
		void OpenglVertexBuffer::Bind() const
		{
			GLOP_PROFILE_FUNCTION();

			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
		}
		void OpenglVertexBuffer::Unbind() const
		{
			GLOP_PROFILE_FUNCTION();

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void OpenglVertexBuffer::SetData(const void* data, uint32_t size)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}

		// INDEX BUFFER

		OpenglIndexBuffer::OpenglIndexBuffer(uint32_t* indices, uint32_t size) : m_count(size)
		{
			GLOP_PROFILE_FUNCTION();

			glGenBuffers(1, &m_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		}
		OpenglIndexBuffer::~OpenglIndexBuffer()
		{
			GLOP_PROFILE_FUNCTION();

			glDeleteBuffers(1, &m_buffer_id);
		}
		void OpenglIndexBuffer::Bind() const
		{
			GLOP_PROFILE_FUNCTION();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
		}
		void OpenglIndexBuffer::Unbind() const
		{
			GLOP_PROFILE_FUNCTION();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
