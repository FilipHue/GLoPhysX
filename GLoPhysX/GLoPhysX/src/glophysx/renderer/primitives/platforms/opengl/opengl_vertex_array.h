#pragma once
/**
* @file opengl_vertex_array.h
* @brief Declaration of OpenglVertexArray class.
*
* This header file defines the OpenglVertexArray class, which represents the OpenGL implementation
* for handling vertex arrays in the GLoPhysX renderer. The OpenglVertexArray class provides methods
* for binding, unbinding, adding vertex buffers, adding an index buffer, and retrieving associated
* buffers in an OpenGL vertex array.
*
* @see VertexArray
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/renderer/primitives/vertex_array.h"

namespace GLOPHYSX {
	
	namespace RENDERER {

		class OpenglVertexArray : public VertexArray
		{
		public:
			OpenglVertexArray();
			virtual ~OpenglVertexArray();

			virtual void Bind() override;
			virtual void Unbind() override;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
			virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_vertex_buffers; }
			virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_index_buffer; }

		private:
			uint32_t m_id;
			uint32_t m_index;
			std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
			std::shared_ptr<IndexBuffer> m_index_buffer;
		};
	}
}
