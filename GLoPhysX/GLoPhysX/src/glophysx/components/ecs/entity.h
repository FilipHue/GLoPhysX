#pragma once

#include "components.h"
#include "glophysx/components/scene/scene.h"

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

				T& component = m_scene->m_registry.emplace<T>(m_entity_handle, std::forward<Args>(args)...);
				m_scene->OnComponentAdded<T>(*this, component);

				return component;
			}

			template<typename T, typename... Args>
			T& AddOrReplaceComponent(Args&&... args)
			{
				T& component = m_scene->m_registry.emplace_or_replace<T>(m_entity_handle, std::forward<Args>(args)...);
				m_scene->OnComponentAdded<T>(*this, component);

				return component;
			}

			template<typename T>
			size_t RemoveComponent()
			{
				if (!HasComponent<T>()) {
					GLOP_CORE_CRITICAL("Entity doesn't have the component.");
					exit(-1);
				}
				return m_scene->m_registry.remove<T>(m_entity_handle);
			}

			template<typename T>
			T& GetComponent()
			{
				if (!HasComponent<T>()) {
					GLOP_CORE_CRITICAL("Entity doesn't have the component.");
					exit(-1);
				}
				return m_scene->m_registry.get<T>(m_entity_handle);
			}

			template<typename T>
			bool HasComponent()
			{
				return m_scene->m_registry.all_of<T>(m_entity_handle);
			}

			UUID GetID() { return GetComponent<IDComponent>().m_id; }

			bool operator==(const Entity& other) const { return m_entity_handle == other.m_entity_handle && m_scene == other.m_scene; }
			bool operator!=(const Entity& other) const { return !(*this == other); }
			operator bool() const { return m_entity_handle != entt::null; }
			operator uint32_t() const { return (uint32_t)m_entity_handle; }

			operator entt::entity() const { return m_entity_handle; }

		private:
			entt::entity m_entity_handle{ entt::null };
			Scene* m_scene = nullptr;
		};
	}
}
