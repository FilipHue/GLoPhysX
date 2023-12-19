#pragma once

#include "glophysx/rendering/camera/orthographic/orthographic_camera.h"
#include "renderer_2d_data.h"

namespace GLOPHYSX {

	namespace RENDERING {
		
		class Renderer2D
		{
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const OrthographicCamera& camera);
			static void EndScene();

			static void Flush();

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor = 1.f);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tiling_factor = 1.f);

			static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
			static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

			static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor = 1.f);
			static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Shared<Texture2D>& texture, float tiling_factor = 1.f);

			static void ResetStats();
			static const Statistics& GetStats() { return *s_stats; }

		private:
			static Renderer2DData* s_data;
			static Statistics* s_stats;
		};
	}
}
