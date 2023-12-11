#include "gxpch.h"
#include "opengl_renderer_api.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		void OpenglRendererAPI::Init()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		void OpenglRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			glViewport(x, y, width, height);
		}
		void OpenglRendererAPI::SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}
		void OpenglRendererAPI::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void OpenglRendererAPI::DrawIndexed(const Shared<VertexArray>& vertex_array, uint32_t index_count)
		{
			vertex_array->Bind();
			uint32_t count = index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}
}