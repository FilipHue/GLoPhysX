#pragma once

namespace GLOPHYSX {

	namespace RENDERING {

		class Buffer
		{
		public:
			virtual ~Buffer() {};

			virtual void SetData(const void* data, uint32_t size) = 0;
		};
	}
}
