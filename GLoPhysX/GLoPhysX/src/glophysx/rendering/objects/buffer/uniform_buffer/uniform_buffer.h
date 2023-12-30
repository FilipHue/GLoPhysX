#pragma once

#include "glophysx/core/core.h"

#include "glophysx/rendering/objects/buffer/buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class UniformBuffer : public Buffer
		{
		public:
			virtual ~UniformBuffer() {};

			static Shared<UniformBuffer> Create(uint32_t size, uint32_t binding);
		};
	}
}
