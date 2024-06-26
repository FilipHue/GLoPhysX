#pragma once

#include "renderer_2d_data.h"
#include "glophysx/rendering/camera/camera.h"
#include "glophysx/rendering/camera/editor/editor_camera.h"

#include "glophysx/components/ecs/components.h"

namespace GLOPHYSX {

	namespace RENDERING {

		using namespace COMPONENTS;
		
		class Renderer2D
		{
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const Camera& camera);
			static void BeginScene(const SimpleCamera& camera, const glm::mat4& transform);
			static void BeginScene(const EditorCamera& camera);
			static void EndScene();

			static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
			static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entity_id);
			static void DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float tiling_factor);
			static void DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float tiling_factor, int entity_id);

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor = 1.f);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor = 1.f);

			static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
			static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
			static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor = 1.f);
			static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor = 1.f);

			static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness, float fade, int entity_id = -1);

			static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, uint32_t entity_id);
			static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, uint32_t entity_id);
			static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entity_id = -1);

			static void DrawSprite(const glm::mat4& transform, SpriteComponent& sprite, uint32_t entity_id);

			static void DrawQuadP(const glm::mat4& transform, const glm::vec4& color, int offset);

			static void ResetStats();
			static const Statistics& GetStats() { return *s_stats; }

		private:
			static void StartBatch();
			static void EndBatch();
			static void Flush();

		private:
			static Renderer2DData* s_data;
			static Statistics* s_stats;
		};
	}
}
