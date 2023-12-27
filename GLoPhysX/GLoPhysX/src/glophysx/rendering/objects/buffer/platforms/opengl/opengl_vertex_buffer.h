#pragma once

#include "glophysx/rendering/objects/buffer/vertex_buffer/vertex_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglVertexBuffer : public VertexBuffer
		{
		public:
			OpenglVertexBuffer(uint32_t size);
			OpenglVertexBuffer(float* vertices, uint32_t size);
			virtual ~OpenglVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void OpenglVertexBuffer::SetData(const void* data, uint32_t size) override;

			virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
			virtual const BufferLayout& GetLayout() const override { return m_layout; }

		private:
			uint32_t m_buffer_id;

			BufferLayout m_layout;
		};
	}
}
