#pragma once

#include "glophysx/rendering/objects/buffer/index_buffer/index_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglIndexBuffer : public IndexBuffer
		{
		public:
			OpenglIndexBuffer(uint32_t* indices, uint32_t count);
			virtual ~OpenglIndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual uint32_t GetCount() const override { return m_count; }

		private:
			uint32_t m_buffer_id;
			uint32_t m_count;
		};
	}
}
