#include "gxpch.h"
#include "scene.h"

#include "glm.hpp"

#include "glophysx/ecs/entity.h"
#include "glophysx/components/script/scriptable_entity.h"

#include "glophysx/rendering/renderer/2d/renderer_2d.h"

namespace GLOPHYSX {

	using namespace RENDERING;

	namespace COMPONENTS {

		Scene::Scene()
		{
		}

		Scene::~Scene()
		{
		}

		Entity Scene::CreateEntity(const std::string& name)
		{
			Entity entity = { m_registry.create(), this };

			entity.AddComponent<TransformComponent>();

			auto& tag = entity.AddComponent<TagComponent>();
			tag.m_tag = name.empty() ? "Entity" : name;

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

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.m_color, (int)entity);
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

					Renderer2D::DrawQuad(transform.GetTransform(), sprite.m_color, (int)entity);
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
			static_assert(false);
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
