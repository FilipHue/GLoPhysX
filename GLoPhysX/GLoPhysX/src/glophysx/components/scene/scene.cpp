#include "gxpch.h"
#include "scene.h"

#include "glm.hpp"

#include "glophysx/ecs/entity.h"
#include "glophysx/ecs/scriptable_entity.h"

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
		void Scene::OnUpdate(DeltaTime dt)
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
			glm::mat4 camera_transform = glm::mat4(1.f);
			m_registry.view<TransformComponent, CameraComponent>().each([&main_camera, &camera_transform](auto entity, auto& transform, auto& camera)
				{
					if (camera.is_primary == 1) {
						main_camera = &camera.m_camera;
						camera_transform = transform.m_transform;
						return;
					}
				});
			
			if (main_camera != nullptr)
			{
				Renderer2D::BeginScene(*main_camera, camera_transform);

				auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);

				for (auto entity : group) {
					auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

					Renderer2D::DrawQuad(transform.m_transform, sprite.m_color);
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
	}
}
