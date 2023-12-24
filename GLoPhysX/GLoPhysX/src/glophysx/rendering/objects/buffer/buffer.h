#pragma once
/**
* @file buffer.h
* @brief Declaration of VertexBuffer and IndexBuffer classes.
*
* This header file defines the VertexBuffer and IndexBuffer classes, which represent the abstraction
* for handling vertex and index buffers in the GLoPhysX renderer. These classes provide interfaces for
* binding, unbinding, setting layouts, and creating buffers.
*
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"
#include "buffer_layout.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class VertexBuffer {
		public:
			GLOP_API virtual ~VertexBuffer() {};

			GLOP_API virtual void Bind() const = 0;
			GLOP_API virtual void Unbind() const = 0;

			GLOP_API virtual void SetData(const void* data, uint32_t size) = 0;

			GLOP_API virtual void SetLayout(const BufferLayout& layout) = 0;
			GLOP_API virtual const BufferLayout& GetLayout() const = 0;

			GLOP_API static std::shared_ptr<VertexBuffer> Create(uint32_t size);
			GLOP_API static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
		};

		class IndexBuffer {
		public:
			GLOP_API virtual ~IndexBuffer() {};

			GLOP_API virtual void Bind() const = 0;
			GLOP_API virtual void Unbind() const = 0;

			GLOP_API virtual uint32_t GetCount() const = 0;

			GLOP_API static std::shared_ptr<IndexBuffer> Create(uint32_t* vertices, uint32_t count);
		};
	}
}
