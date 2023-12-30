#pragma once

#include "glophysx/rendering/objects/buffer/vertex_buffer/vertex_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglVertexBuffer : public VertexBuffer
		{
		public:
			OpenglVertexBuffer(uint32_t size);
			OpenglVertexBuffer(float* vertices, uint32_t size);
			~OpenglVertexBuffer();

			void Bind() const override;
			void Unbind() const override;

			void OpenglVertexBuffer::SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

			void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
			const BufferLayout& GetLayout() const override { return m_layout; }

		private:
			uint32_t m_buffer_id;

			BufferLayout m_layout;
		};
	}
}
