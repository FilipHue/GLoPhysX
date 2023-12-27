#include "gxpch.h"
#include "opengl_shader_storage_buffer.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglShaderStorageBuffer::OpenglShaderStorageBuffer(uint32_t size, uint32_t binding)
		{
			glCreateBuffers(1, &m_id);
			glNamedBufferData(m_id, size, nullptr, GL_STATIC_DRAW);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_id);
		}

		OpenglShaderStorageBuffer::~OpenglShaderStorageBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenglShaderStorageBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
		{
			glNamedBufferSubData(m_id, offset, size, data);
		}
	}
}
