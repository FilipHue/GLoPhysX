#include "gxpch.h"
#include "mesh.h"

namespace GLOPHYSX {

	namespace RENDERING {

		namespace COMPONENTS {

			Mesh::Mesh(std::vector<float>& vertices, std::vector<uint32_t>& indices, BufferLayout& layout)
			{
				m_vertex_array		= VertexArray::Create();
				m_vertex_buffer		= VertexBuffer::Create(vertices.data(), sizeof(*vertices.data()) * vertices.size());
				m_index_buffer		= IndexBuffer::Create(indices.data(), indices.size());

				m_vertex_buffer->SetLayout(layout);

				m_vertex_array->AddVertexBuffer(m_vertex_buffer);
				m_vertex_array->AddIndexBuffer(m_index_buffer);
			}
		}
	}
}
