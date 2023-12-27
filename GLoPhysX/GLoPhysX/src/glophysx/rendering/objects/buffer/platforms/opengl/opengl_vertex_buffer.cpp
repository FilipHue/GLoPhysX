#include "gxpch.h"
#include "opengl_vertex_buffer.h"

#ifdef GLOP_DEBUG
#include "glophysx/debug/debug.h"
#endif

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

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
	}
}
