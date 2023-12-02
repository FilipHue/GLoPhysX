#include "gxpch.h"
#include "renderer.h"

namespace GLOPHYSX {

	namespace RENDERER {

		glm::mat4 Renderer::m_vp_scene_matrix = glm::mat4(1.f);

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

		void Renderer::BeginScene(const std::shared_ptr<Camera> camera)
		{
			m_vp_scene_matrix = camera->GetVPMatrix();
		}

		void Renderer::EndScene()
		{
		}

		void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4 model_matrix, uint32_t index_count)
		{
			shader->Bind();
			vertex_array->Bind();

			shader->SetMat4("u_view_projection", m_vp_scene_matrix);
			shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(vertex_array, index_count);
		}
	}
}

