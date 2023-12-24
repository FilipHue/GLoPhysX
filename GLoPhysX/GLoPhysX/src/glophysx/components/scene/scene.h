#pragma once

#include "glophysx/core/core.h"
#include "glophysx/core/time/time.h"

#include "glophysx/rendering/camera/editor/editor_camera.h"

#include "entt/entt.h"

namespace GLOPHYSX {

	namespace EDITOR {
		class SceneHierarchy;
	}
	using namespace EDITOR;
	using namespace RENDERING;

	namespace COMPONENTS {

		class Entity;

		class Scene
		{
		public:
			Scene();
			virtual ~Scene();

			Entity CreateEntity(const std::string& name = std::string());
			void DestroyEntity(Entity& entity);

			void OnUpdateEditor(DeltaTime dt, EditorCamera& camera);
			void OnUpdateRuntime(DeltaTime dt);

			void OnViewportResize(uint32_t width, uint32_t height);

			Entity GetPrimaryCameraEntity();

		private:
			template<typename T>
			void OnComponentAdded(Entity entity, T& component);

		private:
			entt::registry m_registry;

			uint32_t m_viewport_width;
			uint32_t m_viewport_height;

			friend class Entity;
			friend class SceneSerializer;
			friend class SceneHierarchy;
		};
	}
}
