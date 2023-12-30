#include "gxpch.h"
#include "opengl_shader_storage_buffer.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglShaderStorageBuffer::OpenglShaderStorageBuffer(uint32_t size, uint32_t binding)
		{
			glCreateBuffers(1, &m_id);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_id);
		}

		OpenglShaderStorageBuffer::~OpenglShaderStorageBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void OpenglShaderStorageBuffer::Bind() const
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		}

		void OpenglShaderStorageBuffer::Unbind() const
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}

		void OpenglShaderStorageBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
		{
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
		}

		void OpenglShaderStorageBuffer::Synchronise()
		{
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		}
	}
}
