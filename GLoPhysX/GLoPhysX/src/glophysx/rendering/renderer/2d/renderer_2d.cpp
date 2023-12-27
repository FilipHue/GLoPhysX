#include "gxpch.h"
#include "renderer_2d.h"

#include "renderer_2d_data.h"
#include "glophysx/rendering/renderer/commands/renderer_commands.h"

#ifdef GLOP_DEBUG
	#include "glophysx/debug/debug.h"
#endif

#include "gtc/matrix_transform.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		Renderer2DData* Renderer2D::s_data = nullptr;
		Statistics* Renderer2D::s_stats = new Statistics();

		void Renderer2D::Init()
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data == nullptr) {
				s_data = new Renderer2DData();
			}

			s_data->quad_data = MakeShared<QuadData>();

			s_data->quad_data->VA = VertexArray::Create();

			s_data->quad_data->VB = VertexBuffer::Create(s_data->maximum_vertices * sizeof(QuadVertexData));
			s_data->quad_data->VB->SetLayout({
				{ShaderDataType::Float3, "a_position"},
				{ShaderDataType::Float4, "a_color"},
				{ShaderDataType::Float2, "a_texture_coord"},
				{ShaderDataType::Float, "a_texture_index"},
				{ShaderDataType::Float, "a_tiling_factor"},
				{ShaderDataType::Int, "a_entity_id"}
			});
			s_data->quad_data->VA->AddVertexBuffer(s_data->quad_data->VB);
			s_data->quad_data->VB_base = new QuadVertexData[s_data->maximum_vertices];

			uint32_t offset = 0;
			uint32_t* quad_data_indices = new uint32_t[s_data->maximum_indices];
			if (s_data->maximum_indices >= 6) {
				for (uint32_t i = 0; i < s_data->maximum_indices; i += 6) {
					quad_data_indices[i + 0] = offset + 0;
					quad_data_indices[i + 1] = offset + 1;
					quad_data_indices[i + 2] = offset + 2;

					quad_data_indices[i + 3] = offset + 2;
					quad_data_indices[i + 4] = offset + 3;
					quad_data_indices[i + 5] = offset + 0;

					offset += 4;
				}
			}
			s_data->quad_data->IB = IndexBuffer::Create(quad_data_indices, s_data->maximum_indices);
			s_data->quad_data->VA->AddIndexBuffer(s_data->quad_data->IB);
			delete[] quad_data_indices;

			s_data->white_texture = Texture2D::Create(1, 1);
			uint32_t white_texture_data = 0xffffffff;
			s_data->white_texture->SetData(&white_texture_data, sizeof(uint32_t));

			int32_t samplers[s_data->maximum_texture_slots]{};
			for (uint32_t i = 0; i < s_data->maximum_texture_slots; i++) {
				samplers[i] = i;
			}

			s_data->shader = Shader::Create("assets/shaders/normal.glsl");

			s_data->texture_slots[0] = s_data->white_texture;

			s_data->camera_uniform_buffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
		}

		void Renderer2D::Shutdown()
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data != nullptr) {
				delete[] s_data->quad_data->VB_base;
				delete s_data;
				s_data = nullptr;
			}
		}

		void Renderer2D::BeginScene(const Camera& camera)
		{
			GLOP_PROFILE_FUNCTION();

			s_data->camera_buffer.view_projection = camera.GetVPMatrix();
			s_data->camera_uniform_buffer->SetData(&(s_data->camera_buffer), sizeof(Renderer2DData::CameraData));

			StartBatch();
		}

		void Renderer2D::BeginScene(const SimpleCamera& camera, const glm::mat4& transform)
		{
			GLOP_PROFILE_FUNCTION();

			s_data->camera_buffer.view_projection = camera.GetProjectionMatrix() * glm::inverse(transform);
			s_data->camera_uniform_buffer->SetData(&(s_data->camera_buffer), sizeof(Renderer2DData::CameraData));

			StartBatch();
		}

		void Renderer2D::BeginScene(const EditorCamera& camera)
		{
			GLOP_PROFILE_FUNCTION();

			s_data->camera_buffer.view_projection = camera.GetVPMatrix();
			s_data->camera_uniform_buffer->SetData(&(s_data->camera_buffer), sizeof(Renderer2DData::CameraData));

			StartBatch();
		}

		void Renderer2D::EndScene()
		{
			GLOP_PROFILE_FUNCTION();

			Flush();
		}

		void Renderer2D::StartBatch()
		{
			GLOP_PROFILE_FUNCTION();

			s_data->quad_data->index_count = 0;
			s_data->quad_data->VB_ptr = s_data->quad_data->VB_base;

			s_data->texture_slot_index = 1;
		}

		void Renderer2D::EndBatch()
		{
			GLOP_PROFILE_FUNCTION();

			EndScene();
		}

		void Renderer2D::Flush()
		{
			GLOP_PROFILE_FUNCTION();

			uint32_t data_size = (uint32_t)((uint8_t*)s_data->quad_data->VB_ptr - (uint8_t*)s_data->quad_data->VB_base);
			if (data_size)
			{
				s_data->shader->Bind();

				for (uint32_t i = 0; i < s_data->texture_slot_index; i++) {
					s_data->texture_slots[i]->Bind(i);
				}

				s_data->quad_data->VB->SetData(s_data->quad_data->VB_base, data_size);

				RendererCommands::DrawIndexed(s_data->quad_data->VA, s_data->quad_data->index_count);

				s_stats->draw_calls++;
			}
		}

		void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data->quad_data->index_count >= s_data->maximum_indices) {
				EndBatch();
				StartBatch();
			}

			for (int i = 0; i < 4; i++) {
				s_data->quad_data->VB_ptr->position = transform * s_data->quad_data->vertex_positions_default[i];
				s_data->quad_data->VB_ptr->color = color;
				s_data->quad_data->VB_ptr->texture_coord = s_data->quad_data->vertex_tex_coords_default[i];
				s_data->quad_data->VB_ptr->texture_index = 0;
				s_data->quad_data->VB_ptr->tiling_factor = 1.0f;
				s_data->quad_data->VB_ptr->entity_id = -1;
				s_data->quad_data->VB_ptr++;
			}

			s_data->quad_data->index_count += 6;

			s_stats->quad_count++;
		}

		void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, uint32_t entity_id)
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data->quad_data->index_count >= s_data->maximum_indices) {
				EndBatch();
				StartBatch();
			}

			for (int i = 0; i < 4; i++) {
				s_data->quad_data->VB_ptr->position = transform * s_data->quad_data->vertex_positions_default[i];
				s_data->quad_data->VB_ptr->color = color;
				s_data->quad_data->VB_ptr->texture_coord = s_data->quad_data->vertex_tex_coords_default[i];
				s_data->quad_data->VB_ptr->texture_index = 0;
				s_data->quad_data->VB_ptr->tiling_factor = 1.0f;
				s_data->quad_data->VB_ptr->entity_id = entity_id;
				s_data->quad_data->VB_ptr++;
			}

			s_data->quad_data->index_count += 6;

			s_stats->quad_count++;
		}

		void Renderer2D::DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float tiling_factor)
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data->quad_data->index_count >= s_data->maximum_indices) {
				EndBatch();
				StartBatch();
			}

			constexpr glm::vec4 color = glm::vec4(1.0f);

			float texture_index = 0.f;
			for (uint32_t i = 1; i < s_data->texture_slot_index; i++) {
				if (*s_data->texture_slots[i].get() == *texture.get()) {
					texture_index = (float)i;
					break;
				}
			}

			if (texture_index == 0.f) {
				texture_index = (float)s_data->texture_slot_index;
				s_data->texture_slots[s_data->texture_slot_index] = texture;
				s_data->texture_slot_index++;
			}

			for (int i = 0; i < 4; i++) {
				s_data->quad_data->VB_ptr->position = transform * s_data->quad_data->vertex_positions_default[i];
				s_data->quad_data->VB_ptr->color = color;
				s_data->quad_data->VB_ptr->texture_coord = s_data->quad_data->vertex_tex_coords_default[i];
				s_data->quad_data->VB_ptr->texture_index = texture_index;
				s_data->quad_data->VB_ptr->tiling_factor = tiling_factor;
				s_data->quad_data->VB_ptr->entity_id = -1;
				s_data->quad_data->VB_ptr++;
			}

			s_data->quad_data->index_count += 6;

			s_stats->quad_count++;
		}

		void Renderer2D::DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float tiling_factor, uint32_t entity_id)
		{
			GLOP_PROFILE_FUNCTION();

			if (s_data->quad_data->index_count >= s_data->maximum_indices) {
				EndBatch();
				StartBatch();
			}

			constexpr glm::vec4 color = glm::vec4(1.0f);

			float texture_index = 0.f;
			for (uint32_t i = 1; i < s_data->texture_slot_index; i++) {
				if (*s_data->texture_slots[i].get() == *texture.get()) {
					texture_index = (float)i;
					break;
				}
			}

			if (texture_index == 0.f) {
				texture_index = (float)s_data->texture_slot_index;
				s_data->texture_slots[s_data->texture_slot_index] = texture;
				s_data->texture_slot_index++;
			}

			for (int i = 0; i < 4; i++) {
				s_data->quad_data->VB_ptr->position = transform * s_data->quad_data->vertex_positions_default[i];
				s_data->quad_data->VB_ptr->color = color;
				s_data->quad_data->VB_ptr->texture_coord = s_data->quad_data->vertex_tex_coords_default[i];
				s_data->quad_data->VB_ptr->texture_index = texture_index;
				s_data->quad_data->VB_ptr->tiling_factor = tiling_factor;
				s_data->quad_data->VB_ptr->entity_id = entity_id;
				s_data->quad_data->VB_ptr++;
			}

			s_data->quad_data->index_count += 6;

			s_stats->quad_count++;
		}

		void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			DrawQuad({ position.x, position.y, 0.0f }, size, color);
		}

		void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.0f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.0f });

			DrawQuad(model_matrix, color);
		}

		void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor)
		{
			GLOP_PROFILE_FUNCTION();

			DrawQuad({ position.x, position.y, 0.0f }, size, texture);
		}

		void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.0f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.0f });

			DrawQuad(model_matrix, texture, tiling_factor);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			DrawRotatedQuad({ position.x, position.y, 0.f }, size, rotation, color);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.0f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::rotate(model_matrix, rotation, { 0.0f, 0.0f, 1.0f });
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.0f });

			DrawQuad(model_matrix, color);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor)
		{
			GLOP_PROFILE_FUNCTION();

			DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor);
		}

		void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor)
		{
			GLOP_PROFILE_FUNCTION();

			glm::mat4 model_matrix = glm::mat4(1.0f);

			model_matrix = glm::translate(model_matrix, position);
			model_matrix = glm::rotate(model_matrix, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
			model_matrix = glm::scale(model_matrix, { size.x, size.y, 1.0f });

			DrawQuad(model_matrix, texture, tiling_factor);
		}

		void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteComponent& sprite, uint32_t entity_id)
		{
			GLOP_PROFILE_FUNCTION();

			if (sprite.m_texture)
			{
				DrawQuad(transform, sprite.m_texture, sprite.m_tiling, entity_id);
			}
			else
			{
				DrawQuad(transform, sprite.m_color, entity_id);
			}
		}

		void Renderer2D::ResetStats()
		{
			GLOP_PROFILE_FUNCTION();

			Statistics::ResetStats(*s_stats);
		}
	}
}
