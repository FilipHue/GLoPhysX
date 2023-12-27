#include "gxpch.h"
#include "opengl_vertex_array.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglVertexArray::OpenglVertexArray()
		{
			GLOP_PROFILE_FUNCTION();

			m_id = 1;
			m_index = 0;
			glCreateVertexArrays(1, &m_id);
		}

		OpenglVertexArray::~OpenglVertexArray()
		{
			GLOP_PROFILE_FUNCTION();

			glDeleteVertexArrays(1, &m_id);
		}

		void OpenglVertexArray::Bind()
		{
			GLOP_PROFILE_FUNCTION();

			glBindVertexArray(m_id);
		}

		void OpenglVertexArray::Unbind()
		{
			GLOP_PROFILE_FUNCTION();

			glBindVertexArray(0);
		}

		void OpenglVertexArray::AddVertexBuffer(const Shared<VertexBuffer>& vertex_buffer)
		{	
			GLOP_PROFILE_FUNCTION();

			if (vertex_buffer->GetLayout().GetElements().size() == 0) {
				GLOP_CORE_WARN("Please provide the elements for the layout");
				exit(-1);
			}

			glBindVertexArray(m_id);
			vertex_buffer->Bind();

			const auto& layout = vertex_buffer->GetLayout();
			for (const auto& element : layout) {

				switch (element.type)
				{
				case ShaderDataType::Int:
				{
					glEnableVertexAttribArray(m_index);
					glVertexAttribIPointer(
						m_index,
						element.GetComponentCount(),
						GL_INT,
						layout.GetStride(),
						(const void*)(UINT_PTR)element.offset
					);
					m_index++;
					break;
				}

				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_index);
					glVertexAttribIPointer(
						m_index,
						element.GetComponentCount(),
						GL_INT,
						layout.GetStride(),
						(const void*)(UINT_PTR)element.offset
					);
					m_index++;
					break;
				}

				default:
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
					break;
				}

			}

			m_vertex_buffers.push_back(vertex_buffer);
		}

		void OpenglVertexArray::AddIndexBuffer(const Shared<IndexBuffer>& index_buffer)
		{
			GLOP_PROFILE_FUNCTION();

			glBindVertexArray(m_id);
			index_buffer->Bind();
			m_index_buffer = index_buffer;
		}
	}
}
