#pragma once

#include "glophysx/core/core.h"

#include "glophysx/rendering/objects/buffer/buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class ShaderStorageBuffer : public Buffer
		{
		public:
			virtual ~ShaderStorageBuffer() {};

			static Shared<ShaderStorageBuffer> Create(uint32_t size, uint32_t binding = 0);
		};
	}
}
