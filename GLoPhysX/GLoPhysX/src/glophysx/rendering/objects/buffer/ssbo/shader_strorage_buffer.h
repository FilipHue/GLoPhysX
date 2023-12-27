#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class ShaderStorageBuffer
		{
		public:
			virtual ~ShaderStorageBuffer() {};

			virtual void SetData(const void* data, uint32_t size, uint32_t offset) = 0;

			static Shared<ShaderStorageBuffer> Create(uint32_t size, uint32_t binding);
		};
	}
}
