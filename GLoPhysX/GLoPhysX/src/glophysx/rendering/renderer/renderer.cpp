#include "gxpch.h"
#include "renderer.h"

#include "2d/renderer_2d.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace RENDERING {

		glm::mat4 Renderer::m_vp_scene_matrix = glm::mat4(1.f);

		void Renderer::Init()
		{
			GLOP_PROFILE_FUNCTION();

			RendererCommands::Init();
			Renderer2D::Init();
		}

		void Renderer::ShutDown()
		{
			GLOP_PROFILE_FUNCTION();
		}

		void Renderer::OnWindowResize(uint32_t width, uint32_t height)
		{
			GLOP_PROFILE_FUNCTION();

			RendererCommands::SetViewport(0, 0, width, height);
		}

		void Renderer::BeginScene(const Shared<Camera>& camera)
		{
			GLOP_PROFILE_FUNCTION();

			m_vp_scene_matrix = camera->GetVPMatrix();
		}

		void Renderer::EndScene()
		{
			GLOP_PROFILE_FUNCTION();
		}

		void Renderer::Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vertex_array, const glm::mat4& model_matrix, uint32_t index_count)
		{
			GLOP_PROFILE_FUNCTION();

			shader->Bind();

			shader->SetMat4("u_view_projection", m_vp_scene_matrix);
			shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(vertex_array, index_count);
		}

		void Renderer::Submit(const Shared<Shader>& shader, const Unique<Mesh>& mesh, const glm::mat4& model_matrix)
		{
			GLOP_PROFILE_FUNCTION();

			shader->Bind();

			shader->SetMat4("u_view_projection", m_vp_scene_matrix);
			shader->SetMat4("u_model", model_matrix);

			mesh->GetVertexArray()->Bind();

			RendererCommands::DrawIndexed(mesh->GetVertexArray(), mesh->GetIndicesCount());


		}
	}
}
