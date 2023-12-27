#include "gxpch.h"
#include "opengl_index_buffer.h"

#ifdef GLOP_DEBUG
#include "glophysx/debug/debug.h"
#endif

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

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
