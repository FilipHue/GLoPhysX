#include "gxpch.h"
#include "scene.h"

#include "glm.hpp"

#include "glophysx/components/ecs/entity.h"
#include "glophysx/components/script/scriptable_entity.h"

#include "glophysx/rendering/renderer/2d/renderer_2d.h"

namespace GLOPHYSX {

	using namespace RENDERING;

	namespace COMPONENTS {

		template<typename T>
		static void CopyComponent(entt::registry& dst, entt::registry& src, std::unordered_map<UUID, entt::entity>& entt_map)
		{
			auto view = src.view<T>();
			for (auto src_entity : view)
			{
				UUID uuid = src.get<IDComponent>(src_entity).m_id;
				if (entt_map.find(uuid) == entt_map.end())
				{
					GLOP_CORE_CRITICAL("Entityt isn't in the map.");
				}
				entt::entity dst_entt_id = entt_map.at(uuid);

				auto& src_component = src.get<T>(src_entity);
				dst.emplace_or_replace<T>(dst_entt_id, src_component);
			}
		}

		template<typename T>
		static void CopyComponentIfExists(Entity dst, Entity src)
		{
			if (src.HasComponent<T>())
			{
				dst.AddOrReplaceComponent<T>(src.GetComponent<T>());
			}
		}

		Shared<Scene> Scene::Copy(Shared<Scene> other)
		{
			Shared<Scene> new_scene = MakeShared<Scene>();

			new_scene->m_viewport_width = other->m_viewport_width;
			new_scene->m_viewport_width = other->m_viewport_width;

			auto& src_scene_reg = other->m_registry;
			auto& dst_scene_reg = new_scene->m_registry;
			std::unordered_map<UUID, entt::entity> entt_map;

			auto id_view = src_scene_reg.view<IDComponent>();
			for (auto entity : id_view)
			{
				std::cout << "1\n";
				UUID uuid = src_scene_reg.get<IDComponent>(entity).m_id;
				const auto& name = src_scene_reg.get<TagComponent>(entity).m_tag;
				Entity new_entity = new_scene->CreateEntityWithUUID(uuid, name);
				entt_map[uuid] = (entt::entity)new_entity;
			}

			CopyComponent<TransformComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<SpriteComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<CameraComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<NativeScriptComponent>(dst_scene_reg, src_scene_reg, entt_map);

			return new_scene;
		}

		Entity Scene::CreateEntity(const std::string& name)
		{
			return CreateEntityWithUUID(UUID(), name);
		}

		Entity Scene::CreateEntityWithUUID(UUID id, const std::string& name)
		{
			Entity entity = { m_registry.create(), this };

			entity.AddComponent<IDComponent>(id);
			auto& tag = entity.AddComponent<TagComponent>();
			tag.m_tag = name.empty() ? "Entity" : name;
			entity.AddComponent<TransformComponent>();

			return entity;
		}

		void Scene::DestroyEntity(Entity& entity)
		{
			m_registry.destroy(entity);
		}

		void Scene::OnUpdateEditor(DeltaTime dt, EditorCamera& camera)
		{
			Renderer2D::BeginScene(camera);

			auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);

			for (auto entity : group) {
				auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}

		void Scene::OnUpdateRuntime(DeltaTime dt)
		{
			{
				m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
					{
						if (!nsc.m_instance)
						{
							nsc.m_instance = nsc.InstantiateScript();
							nsc.m_instance->m_entity = Entity{ entity, this };
							nsc.m_instance->OnCreate();
						}

						nsc.m_instance->OnUpdate(dt);
					});
			}

			SceneCamera* main_camera = nullptr;
			glm::mat4 camera_transform;
			m_registry.view<TransformComponent, CameraComponent>().each([&main_camera, &camera_transform](auto entity, auto& transform, auto& camera)
				{
					if (camera.is_primary == 1) {
						main_camera = &camera.m_camera;
						camera_transform = transform.GetTransform();
						return;
					}
				});

			if (main_camera)
			{
				Renderer2D::BeginScene(*main_camera, camera_transform);

				auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
				for (auto entity : group) {
					auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

					Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
				}

				Renderer2D::EndScene();
			}
		}

		void Scene::OnViewportResize(uint32_t width, uint32_t height)
		{
			m_viewport_width = width;
			m_viewport_height = height;

			auto view = m_registry.view<CameraComponent>();
			for (auto entity : view) {
				auto& camera_component = view.get<CameraComponent>(entity);
				if (!camera_component.fixed_aspect_ratio) {
					camera_component.m_camera.SetViewportSize(width, height);
				}
			}
		}

		Entity Scene::DuplicateEntity(Entity entity)
		{
			std::string name = entity.GetComponent<TagComponent>().m_tag + "(copy)";
			Entity new_entity = CreateEntity(name);

			CopyComponentIfExists<TransformComponent>(new_entity, entity);
			CopyComponentIfExists<SpriteComponent>(new_entity, entity);
			CopyComponentIfExists<CameraComponent>(new_entity, entity);
			CopyComponentIfExists<NativeScriptComponent>(new_entity, entity);

			return new_entity;
		}

		Entity Scene::GetPrimaryCameraEntity()
		{
			auto view = m_registry.view<CameraComponent>();

			for (auto entity : view)
			{
				const auto& camera = view.get<CameraComponent>(entity);
				if (camera.is_primary)
				{
					return Entity{ entity, this };
				}
			}

			return {};
		}

		template<typename T>
		void Scene::OnComponentAdded(Entity entity, T& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
		{
			component.m_camera.SetViewportSize(m_viewport_width, m_viewport_height);
		}

		template<>
		void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
		{
		}
	}
}
