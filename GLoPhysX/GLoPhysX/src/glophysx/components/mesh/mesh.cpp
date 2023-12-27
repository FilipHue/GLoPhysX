#include "gxpch.h"
#include "mesh.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace COMPONENTS {

		Mesh::Mesh(std::vector<float>& vertices, std::vector<uint32_t>& indices, BufferLayout& layout)
		{
			GLOP_PROFILE_FUNCTION();

			m_vertex_array		= VertexArray::Create();
			m_vertex_buffer		= VertexBuffer::Create(vertices.data(), sizeof(*vertices.data()) * (uint32_t)vertices.size());
			m_index_buffer		= IndexBuffer::Create(indices.data(), (uint32_t)indices.size());

			m_vertex_buffer->SetLayout(layout);

			m_vertex_array->AddVertexBuffer(m_vertex_buffer);
			m_vertex_array->AddIndexBuffer(m_index_buffer);
		}
	}
}
