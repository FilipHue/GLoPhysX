#include "gxpch.h"
#include "renderer_2d.h"

#include "glophysx/rendering/objects/vertex_array.h"
#include "glophysx/rendering/shader/shader.h"

#include "glophysx/rendering/renderer/commands/renderer_commands.h"

#include "gtc/matrix_transform.hpp"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

namespace GLOPHYSX {

	namespace RENDERING {

		struct Renderer2DData {
			Shared<VertexArray> quad_VA;
			Shared<Shader> shader;
			Shared<Texture2D> white_texture;
		};

		static Renderer2DData* s_data;

		void Renderer2D::Init()
		{
			GLOP_PROFILE_FUNCTION();

			s_data = new Renderer2DData();

			s_data->quad_VA = VertexArray::Create();

			std::vector<float> sq_vertices = {
				   -0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
					0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
					0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
				   -0.5f,  0.5f, 0.0f,	0.0f, 1.0f
			};
			std::vector<unsigned int> sq_indices = { 0, 1, 2, 2, 3, 0 };
			BufferLayout sq_layout = {
				{ShaderDataType::Float3, "a_position"},
				{ShaderDataType::Float2, "a_texcoord"}
			};

			Shared<VertexBuffer> quad_VB = VertexBuffer::Create(sq_vertices.data(), sizeof(*sq_vertices.data()) * sq_vertices.size());
			Shared<IndexBuffer> quad_IB = IndexBuffer::Create(sq_indices.data(), sq_indices.size());

			quad_VB->SetLayout(sq_layout);

			s_data->quad_VA->AddVertexBuffer(quad_VB);
			s_data->quad_VA->AddIndexBuffer(quad_IB);

			s_data->shader = Shader::Create("assets/shaders/normal.glsl");
			s_data->shader->Bind();
			s_data->shader->SetInt("u_texture", 0);

			s_data->white_texture = Texture2D::Create(1, 1);
			uint32_t white_texture_data = 0xffffffff;
			s_data->white_texture->SetData(&white_texture_data, sizeof(uint32_t));
		}

		void Renderer2D::Shutdown()
		{
			GLOP_PROFILE_FUNCTION();

			delete s_data;
		}

		void Renderer2D::BeginScene(const OrthographicCamera& camera)
		{
			GLOP_PROFILE_FUNCTION();

			s_data->shader->Bind();
			s_data->shader->SetMat4("u_view_projection", camera.GetVPMatrix());
		}

		void Renderer2D::EndScene()
		{
			GLOP_PROFILE_FUNCTION();
		}

		void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			DrawQuad({ position.x, position.y, 0.f }, size, color);
		}

		void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.f });

			s_data->white_texture->Bind();
			s_data->shader->SetVec3("u_color", color);
			s_data->shader->SetFloat("u_tiling_factor", 1.f);
			s_data->shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(s_data->quad_VA);
		}

		void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture)
		{
			GLOP_PROFILE_FUNCTION();

			DrawQuad({ position.x, position.y, 0.f }, size, texture);
		}

		void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.f });

			texture->Bind();
			s_data->shader->SetVec3("u_color", glm::vec3(1.f, 1.f, 1.f));
			s_data->shader->SetFloat("u_tiling_factor", 1.f);
			s_data->shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(s_data->quad_VA);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			DrawRotatedQuad({ position.x, position.y, 0.f }, size, rotation, color);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::rotate(model_matrix, rotation, {0.f, 0.f, 1.f});
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.f });

			s_data->white_texture->Bind();
			s_data->shader->SetVec3("u_color", color);
			s_data->shader->SetFloat("u_tiling_factor", 1.f);
			s_data->shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(s_data->quad_VA);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture)
		{
			GLOP_PROFILE_FUNCTION();

			DrawRotatedQuad({ position.x, position.y, 0.f }, size, rotation, texture);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::rotate(model_matrix, rotation, { 0.f, 0.f, 1.f });
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.f });

			texture->Bind();
			s_data->shader->SetVec3("u_color", glm::vec3(1.f, 1.f, 1.f));
			s_data->shader->SetFloat("u_tiling_factor", 1.f);
			s_data->shader->SetMat4("u_model", model_matrix);

			RendererCommands::DrawIndexed(s_data->quad_VA);
		}
	}
}
