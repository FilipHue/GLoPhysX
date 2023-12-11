#include "gxpch.h"
#include "renderer.h"

namespace GLOPHYSX {

	namespace RENDERING {

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

		void Renderer::BeginScene(const Shared<Camera> camera)
		{
			m_vp_scene_matrix = camera->GetVPMatrix();
		}

		void Renderer::EndScene()
		{
		}

		void Renderer::Submit(const Shared<Shader> shader, const Shared<VertexArray>& vertex_array, const glm::mat4 model_matrix, uint32_t index_count)
		{
			shader->Bind();

			shader->SetMat4("u_view_projection", m_vp_scene_matrix);
			shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(vertex_array, index_count);
		}

		void Renderer::Submit(const Shared<Shader> shader, const Unique<Mesh>& mesh, const glm::mat4 model_matrix)
		{
			shader->Bind();

			shader->SetMat4("u_view_projection", m_vp_scene_matrix);
			shader->SetMat4("u_model", model_matrix);

			mesh->GetVertexArray()->Bind();

			RendererCommands::DrawIndexed(mesh->GetVertexArray(), mesh->GetIndicesCount());


		}
	}
}
