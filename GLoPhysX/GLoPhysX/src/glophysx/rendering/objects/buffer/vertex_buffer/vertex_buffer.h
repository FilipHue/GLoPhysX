#pragma once

#include "glophysx/rendering/objects/buffer/buffer.h"
#include "vertex_buffer_layout.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class VertexBuffer : public Buffer
		{
		public:
			GLOP_API virtual ~VertexBuffer() {};

			GLOP_API virtual void SetLayout(const BufferLayout& layout) = 0;
			GLOP_API virtual const BufferLayout& GetLayout() const = 0;

			GLOP_API static Shared<VertexBuffer> Create(uint32_t size);
			GLOP_API static Shared<VertexBuffer> Create(float* vertices, uint32_t size);
		};
	}
}
