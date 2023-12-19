#pragma once

#include "glophysx/core/core.h"

#include "glophysx/rendering/objects/vertex_array.h"
#include "glophysx/rendering/shader/shader.h"

#include "glophysx/rendering/objects/texture/texture.h"

#include "glm.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		struct QuadVertexData
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texture_coord;
			float texture_index;
			float tiling_factor;
		};

		struct QuadData
		{
			Shared<VertexArray> VA;
			Shared<VertexBuffer> VB;
			Shared<IndexBuffer> IB;

			uint32_t index_count = 0;
			QuadVertexData* VB_base = nullptr;
			QuadVertexData* VB_ptr = VB_base;

			// (0, 0) IN THE LOWER LEFT
			/*glm::vec4 vertex_positions[4] = {
				{0.f, 0.f, 0.f, 1.f},
				{1.f, 0.f, 0.f, 1.f},
				{1.f, 1.f, 0.f, 1.f},
				{0.f, 1.f, 0.f, 1.f}
			};*/

			// (0, 0) IN THE CENTER
			glm::vec4 vertex_positions[4] = {
				{-0.5f, -0.5f, 0.f, 1.f},
				{ 0.5f, -0.5f, 0.f, 1.f},
				{ 0.5f,  0.5f, 0.f, 1.f},
				{-0.5f,  0.5f, 0.f, 1.f}
			};

			glm::vec2 vertex_tex_coords[4] = {
				{0.f, 0.f},
				{1.f, 0.f},
				{1.f, 1.f},
				{0.f, 1.f}
			};
		};

		struct Renderer2DData {
			static const uint32_t maximum_quads = 10000;
			static const uint32_t maximum_vertices = maximum_quads * 4;
			static const uint32_t maximum_indices = maximum_quads * 6;
			static const uint32_t maximum_texture_slots = 32;

			Shared<QuadData> quad_data;

			std::array<Shared<Texture2D>, maximum_texture_slots> texture_slots;
			uint32_t texture_slot_index = 1;

			Shared<Shader> shader;
			Shared<Texture2D> white_texture;
		};

		struct Statistics
		{
			uint32_t draw_calls = 0;
			uint32_t quad_count = 0;

			uint32_t GetVertexCount() const { return quad_count * 4; }
			uint32_t GetIndexCount() const { return quad_count * 6; }

			static void ResetStats(Statistics& stats) {
				stats.draw_calls = 0;
				stats.quad_count = 0;
			}
		};
	}
}
