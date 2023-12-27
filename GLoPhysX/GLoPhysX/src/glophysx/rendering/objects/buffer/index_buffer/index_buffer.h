#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class IndexBuffer
		{
		public:
			GLOP_API virtual ~IndexBuffer() {};

			GLOP_API virtual void Bind() const = 0;
			GLOP_API virtual void Unbind() const = 0;

			GLOP_API virtual uint32_t GetCount() const = 0;

			GLOP_API static Shared<IndexBuffer> Create(uint32_t* vertices, uint32_t count);
		};
	}
}
