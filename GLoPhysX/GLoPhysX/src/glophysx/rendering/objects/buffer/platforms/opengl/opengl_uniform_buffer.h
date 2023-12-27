#pragma once

#include "glophysx/rendering/objects/buffer/uniform_buffer/uniform_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglUniformBuffer : public UniformBuffer
		{
		public:
			OpenglUniformBuffer(uint32_t size, uint32_t binding);
			~OpenglUniformBuffer();

			void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

		private:
			uint32_t m_id;
		};
	}
}
