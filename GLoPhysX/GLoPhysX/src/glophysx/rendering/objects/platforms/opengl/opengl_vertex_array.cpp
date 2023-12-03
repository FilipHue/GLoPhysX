#include "gxpch.h"
#include "opengl_vertex_array.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {
		OpenglVertexArray::OpenglVertexArray()
		{
			m_id = 1;
			m_index = 0;
			glCreateVertexArrays(1, &m_id);
		}
		OpenglVertexArray::~OpenglVertexArray()
		{
			glDeleteVertexArrays(1, &m_id);
		}
		void OpenglVertexArray::Bind()
		{
			glBindVertexArray(m_id);
		}
		void OpenglVertexArray::Unbind()
		{
			glBindVertexArray(0);
		}
		void OpenglVertexArray::AddVertexBuffer(const Shared<VertexBuffer>& vertex_buffer)
		{	
			if (vertex_buffer->GetLayout().GetElements().size() == 0) {
				GLOP_CORE_WARN("Please provide the elements for the layout");
				exit(-1);
			}

			glBindVertexArray(m_id);
			vertex_buffer->Bind();

			const auto& layout = vertex_buffer->GetLayout();
			for (const auto& element : layout) {

				glEnableVertexAttribArray(m_index);
				glVertexAttribPointer(
					m_index,
					element.GetComponentCount(),
					GL_FLOAT,
					GL_FALSE,
					layout.GetStride(),
					(const void*)(UINT_PTR)element.offset
				);

				m_index++;
			}

			m_vertex_buffers.push_back(vertex_buffer);
		}
		void OpenglVertexArray::AddIndexBuffer(const Shared<IndexBuffer>& index_buffer)
		{
			glBindVertexArray(m_id);
			index_buffer->Bind();
			m_index_buffer = index_buffer;
		}
	}
}
