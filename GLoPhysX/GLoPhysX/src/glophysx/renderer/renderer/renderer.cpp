#include "gxpch.h"
#include "renderer.h"

namespace GLOPHYSX {

	namespace RENDERER {

		void Renderer::Init()
		{
			RendererCommands::Init();
		}

		void Renderer::ShutDown()
		{
		}

		void Renderer::OnWindowResize(uint32_t width, uint32_t height)
		{
			RendererCommands::SetViewport(0, 0, width, height);
		}

		void Renderer::BeginScene()
		{
		}

		void Renderer::EndScene()
		{
		}

		void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count)
		{
			shader->Bind();
			vertex_array->Bind();
			RendererCommands::DrawIndexed(vertex_array, index_count);
		}
	}
}

