#pragma once
/**
* @file vertex_array.h
* @brief Declaration of VertexArray class.
*
* This header file defines the VertexArray class, which represents an abstraction for handling vertex
* arrays in the GLoPhysX renderer. The VertexArray class provides a common interface for binding,
* unbinding, adding vertex buffers, adding an index buffer, and retrieving associated buffers.
*
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"

#include "glophysx/rendering/objects/buffer/buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class VertexArray
		{
		public:
			GLOP_API virtual ~VertexArray() = default;

			GLOP_API virtual void Bind() = 0;
			GLOP_API virtual void Unbind() = 0;

			GLOP_API virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertex_buffer) = 0;
			GLOP_API virtual void AddIndexBuffer(const Shared<IndexBuffer>& index_buffer) = 0;

			GLOP_API virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
			GLOP_API virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

			GLOP_API static Shared<VertexArray> Create();
		};
	}
}
