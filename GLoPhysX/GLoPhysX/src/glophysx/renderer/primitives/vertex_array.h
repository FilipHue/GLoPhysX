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

#include "glophysx/renderer/primitives/buffer/buffer.h"

namespace GLOPHYSX {

	namespace RENDERER {

		class VertexArray
		{
		public:
			virtual ~VertexArray() = default;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
			virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;

			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
			virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

			static std::shared_ptr<VertexArray> Create();
		};
	}
}
