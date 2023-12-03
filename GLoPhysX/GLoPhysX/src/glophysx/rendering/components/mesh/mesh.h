#pragma once

#include "glophysx/core/core.h"

#include "glophysx/rendering/renderer/renderer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		namespace COMPONENTS {

			class Mesh
			{
			public:
				Mesh() = delete;
				GLOP_API Mesh(std::vector<float>& vertices, std::vector<uint32_t>& indices, BufferLayout& layout);

				GLOP_API const Shared<VertexArray>& GetVertexArray() const { return m_vertex_array; }

			private:
				Shared<VertexArray> m_vertex_array;
				Shared<VertexBuffer> m_vertex_buffer;
				Shared<IndexBuffer> m_index_buffer;
			};
		}
	}
}
