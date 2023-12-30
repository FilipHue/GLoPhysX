#pragma once

namespace GLOPHYSX {

	namespace RENDERING {

		class Buffer
		{
		public:
			virtual ~Buffer() {};

			virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
		};
	}
}
