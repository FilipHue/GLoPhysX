#include "gxpch.h"
#include "opengl_uniform_buffer.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglUniformBuffer::OpenglUniformBuffer(uint32_t size, uint32_t binding)
		{
			glCreateBuffers(1, &m_id);
			glNamedBufferData(m_id, size, nullptr, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
		}

		OpenglUniformBuffer::~OpenglUniformBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenglUniformBuffer::Bind() const
		{
		}

		void OpenglUniformBuffer::Unbind() const
		{
		}

		void OpenglUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
		{
			glNamedBufferSubData(m_id, offset, size, data);
		}
	}
}
