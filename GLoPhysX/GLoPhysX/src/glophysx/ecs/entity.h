#pragma once

#include "glophysx/components/scene/scene.h"

#include "components.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		class Entity
		{
		public:
			Entity() = default;
			Entity(entt::entity handle, Scene* scene);
			Entity(const Entity& other) = default;

			template<typename T, typename... Args>
			T& AddComponent(Args&&... args)
			{
				if (HasComponent<T>()) {
					GLOP_CORE_CRITICAL("Entity already has the component.");
					exit(-1);
				}
				return m_scene->m_registry.emplace<T>(m_entity_handle, std::forward<Args>(args)...);
			}

			template<typename T>
			T& RemoveComponent()
			{
				if (!HasComponent<T>()) {
					GLOP_CORE_CRITICAL("Entity doesn'y have the component.");
					exit(-1);
				}
				return m_scene->m_registry.remove<T>(m_entity_handle);
			}

			template<typename T>
			T& GetComponent()
			{
				if (!HasComponent<T>()) {
					GLOP_CORE_CRITICAL("Entity doesn'y have the component.");
					exit(-1);
				}
				return m_scene->m_registry.get<T>(m_entity_handle);
			}

			template<typename T>
			bool HasComponent()
			{
				return m_scene->m_registry.all_of<T>(m_entity_handle);
			}

			operator bool() const { return m_entity_handle != entt::null; }

		private:
			entt::entity m_entity_handle{ entt::null };
			Scene* m_scene = nullptr;
		};
	}
}
