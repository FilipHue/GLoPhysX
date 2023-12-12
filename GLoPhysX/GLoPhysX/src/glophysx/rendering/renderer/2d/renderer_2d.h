#pragma once

#include "glophysx/rendering/camera/orthographic/orthographic_camera.h"
#include "glophysx/rendering/objects/texture/texture.h"

namespace GLOPHYSX {

	namespace RENDERING {
		
		class Renderer2D
		{
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const OrthographicCamera& camera);
			static void EndScene();

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture);

		private:

		};
	}
}
