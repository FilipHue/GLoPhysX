#pragma once

#include "glophysx/rendering/objects/buffer/ssbo/shader_strorage_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglShaderStorageBuffer : public ShaderStorageBuffer
		{
		public:
			OpenglShaderStorageBuffer(uint32_t size, uint32_t binding);
			~OpenglShaderStorageBuffer();

			void SetData(const void* data, uint32_t size, uint32_t offset) override;

		private:
			uint32_t m_id;
		};
	}
}
