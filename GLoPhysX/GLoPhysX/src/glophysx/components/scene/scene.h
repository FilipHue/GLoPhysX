#pragma once

#include "glophysx/core/core.h"
#include "glophysx/core/time/time.h"

#include "entt/entt.h"

namespace GLOPHYSX {

	namespace EDITOR {
		class SceneHierarchy;
	}
	using namespace EDITOR;

	namespace COMPONENTS {

		class Entity;

		class Scene
		{
		public:
			Scene();
			virtual ~Scene();

			Entity CreateEntity(const std::string& name = std::string());

			void OnUpdate(DeltaTime dt);

			void OnViewportResize(uint32_t width, uint32_t height);

		private:
			entt::registry m_registry;

			uint32_t m_viewport_width;
			uint32_t m_viewport_height;

			friend class Entity;
			friend class SceneHierarchy;
		};
	}
}
