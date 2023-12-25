#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class Texture
		{
		public:
			virtual ~Texture() = default;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			virtual uint32_t GetID() const = 0;

			virtual void SetData(void* data, uint32_t size) = 0;

			virtual void Bind(uint32_t slot = 0) const = 0;
		};

		class Texture2D : public Texture
		{
		public:
			GLOP_API static Shared<Texture2D> Create(const std::string& path, int flip = 0, uint32_t x_offset = 0, uint32_t y_offset = 0);
			GLOP_API static Shared<Texture2D> Create(uint32_t width, uint32_t height);

			virtual bool operator==(const Texture2D& other) = 0;
		};
	}
}
