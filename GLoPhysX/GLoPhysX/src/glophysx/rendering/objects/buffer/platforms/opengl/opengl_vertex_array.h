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

#include "glophysx/rendering/objects/vertex_array.h"

namespace GLOPHYSX {
	
	namespace RENDERING {

		class OpenglVertexArray : public VertexArray
		{
		public:
			OpenglVertexArray();
			~OpenglVertexArray();

			void Bind() const override;
			void Unbind() const override;

			void AddVertexBuffer(const Shared<VertexBuffer>& vertex_buffer) override;
			void AddIndexBuffer(const Shared<IndexBuffer>& index_buffer) override;

			const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const override { return m_vertex_buffers; }
			const Shared<IndexBuffer>& GetIndexBuffer() const override { return m_index_buffer; }

		private:
			uint32_t m_id;
			uint32_t m_index;
			std::vector<Shared<VertexBuffer>> m_vertex_buffers;
			Shared<IndexBuffer> m_index_buffer;
		};
	}
}
