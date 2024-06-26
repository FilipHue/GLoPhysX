#include "gxpch.h"
#include "scene.h"

#include "glophysx/rendering/renderer/2d/renderer_2d.h"

#include "glophysx/components/ecs/entity.h"
#include "glophysx/components/script/scriptable_entity.h"
#include "glophysx/components/script/lua_script.h"

#include "glophysx/components/scene/debug/scene_debug_draw.h"

#include "glophysx/debug/debug.h"

#include "glm.hpp"

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_edge_shape.h"

SceneDebugDraw m_scene_db_draw;

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
					GLOP_CORE_CRITICAL("Entity isn't in the map.");
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

			new_scene->m_physics_world = other->m_physics_world;

			new_scene->m_viewport_width = other->m_viewport_width;
			new_scene->m_viewport_width = other->m_viewport_width;

			auto& src_scene_reg = other->m_registry;
			auto& dst_scene_reg = new_scene->m_registry;
			std::unordered_map<UUID, entt::entity> entt_map;

			auto id_view = src_scene_reg.view<IDComponent>();
			for (auto entity : id_view)
			{
				UUID uuid = src_scene_reg.get<IDComponent>(entity).m_id;
				const auto& name = src_scene_reg.get<TagComponent>(entity).m_tag;
				Entity new_entity = new_scene->CreateEntityWithUUID(uuid, name);
				entt_map[uuid] = (entt::entity)new_entity;
			}

			CopyComponent<TransformComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<SpriteComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<CircleRendererComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<CameraComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<NativeScriptComponent>(dst_scene_reg, src_scene_reg, entt_map);

			CopyComponent<RigidBody2DComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<BoxCollider2DComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<CircleColliderComponent>(dst_scene_reg, src_scene_reg, entt_map);
			CopyComponent<EdgeColliderComponent>(dst_scene_reg, src_scene_reg, entt_map);

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
			if (m_registry.valid(entity)) {
				m_registry.destroy(entity);
			}
		}

		void Scene::OnRuntimeStart()
		{
			m_physics_world = new b2World({ 0.0f, -9.8f });
			m_scene_db_draw.Init();

			m_scene_db_draw.SetFlags(0x0001 | 0x0002);
			m_physics_world->SetDebugDraw(&m_scene_db_draw);

			auto view = m_registry.view<RigidBody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rigidbody_2d = entity.GetComponent<RigidBody2DComponent>();

				b2BodyDef body_definition;

				body_definition.type = (b2BodyType)rigidbody_2d.type;
				body_definition.position.Set(transform.m_translation.x, transform.m_translation.y);
				body_definition.angle = transform.m_rotation.z;
				body_definition.fixedRotation = rigidbody_2d.fixed_rotation;
				body_definition.bullet = rigidbody_2d.is_bullet;

				if (rigidbody_2d.linear_velocity != glm::vec2(0.f)) {
					body_definition.linearVelocity = b2Vec2(rigidbody_2d.linear_velocity.x, rigidbody_2d.linear_velocity.y);
				}

				b2Body* body = m_physics_world->CreateBody(&body_definition);

				rigidbody_2d.runtime_body = body;

				if (entity.HasComponent<BoxCollider2DComponent>())
				{
					auto& boxcollider_2d = entity.GetComponent<BoxCollider2DComponent>();

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(boxcollider_2d.size.x * transform.m_scale.x, boxcollider_2d.size.y * transform.m_scale.y);

					b2FixtureDef fixture_definition;
					fixture_definition.shape = &collider_shape;
					fixture_definition.density = boxcollider_2d.density;
					fixture_definition.friction = boxcollider_2d.friction;
					fixture_definition.restitution = boxcollider_2d.restitution;
					fixture_definition.restitutionThreshold = boxcollider_2d.restitution_treshold;

					body->CreateFixture(&fixture_definition);
				}

				if (entity.HasComponent<CircleColliderComponent>())
				{
					auto& circle_collider = entity.GetComponent<CircleColliderComponent>();

					b2CircleShape circle_shape;
					circle_shape.m_p.Set(circle_collider.offset.x, circle_collider.offset.y);
					circle_shape.m_radius = circle_collider.radius * transform.m_scale.x;

					b2FixtureDef fixture_definition;
					fixture_definition.shape = &circle_shape;
					fixture_definition.density = circle_collider.density;
					fixture_definition.friction = circle_collider.friction;
					fixture_definition.restitution = circle_collider.restitution;
					fixture_definition.restitutionThreshold = circle_collider.restitution_treshold;

					body->CreateFixture(&fixture_definition);
				}

				if (entity.HasComponent<EdgeColliderComponent>())
				{
					auto& circle_collider = entity.GetComponent<EdgeColliderComponent>();

					b2EdgeShape edge_shape;
					edge_shape.SetTwoSided(
						b2Vec2(circle_collider.start.x * transform.m_scale.x, circle_collider.start.y * transform.m_scale.y),
						b2Vec2(circle_collider.stop.x * transform.m_scale.x, circle_collider.stop.y * transform.m_scale.y)
						);

					body->CreateFixture(&edge_shape, 0.0f);
				}
			}
		}

		void Scene::OnRuntimeShutdown()
		{
			delete m_physics_world;

			m_physics_world = nullptr;
		}

		void Scene::OnUpdateEditor(DeltaTime dt, EditorCamera& camera)
		{
			Renderer2D::BeginScene(camera);

			{
				auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);

				for (auto entity : group) {
					auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

					Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
				}
			}

			{
				auto view = m_registry.view<TransformComponent, CircleRendererComponent>();

				for (auto entity : view) {
					auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);

					Renderer2D::DrawCircle(transform.GetTransform(), circle.m_color, circle.m_thickness, circle.m_fade, (int)entity);
				}
			}

			Renderer2D::EndScene();
		}

		void Scene::OnUpdateRuntime(DeltaTime dt)
		{
			{
				GLOP_PROFILE_SCOPE("Native Script")
				m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
					{
						if (!nsc.m_instance)
						{
							nsc.m_instance = nsc.InstantiateScript();
							nsc.m_instance->m_entity = Entity{ entity, this };
							nsc.m_instance->InitLua(nsc.m_script_file);
							nsc.m_instance->OnCreate();
						}

						nsc.m_instance->OnUpdate(dt);
					});
			}

			OnUpdatePhysics(dt);

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

				{
					auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);

					for (auto entity : group) {
						auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
						Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
					}
				}

				{
					auto view = m_registry.view<TransformComponent, CircleRendererComponent>();

					for (auto entity : view) {
						auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);

						Renderer2D::DrawCircle(transform.GetTransform(), circle.m_color, circle.m_thickness, circle.m_fade, (int)entity);
					}
				}

				/*{
					auto view = m_registry.view<TransformComponent, EdgeColliderComponent>();

					for (auto entity : view) {
						auto [transform, edge] = view.get<TransformComponent, EdgeColliderComponent>(entity);

						Renderer2D::DrawLine(glm::vec3(edge.start, 0.0f) * transform.m_scale + transform.m_translation, glm::vec3(edge.stop, 0.0f) * transform.m_scale + transform.m_translation, glm::vec4(0.f, 1.f, 0.f, 1.f), (int)entity);
					}
				}*/

				m_scene_db_draw.SetProjectionMatrix(main_camera->GetProjectionMatrix() * glm::inverse(camera_transform));
				m_physics_world->DebugDraw();

				m_scene_db_draw.Flush();

				Renderer2D::EndScene();
			}
		}

		void Scene::OnUpdatePhysics(DeltaTime dt)
		{
			const int32_t velocity_iterations = 8;
			const int32_t position_iterations = 3;
			{
				GLOP_PROFILE_SCOPE("Physic Step")
				m_physics_world->Step(dt, velocity_iterations, position_iterations);
			}

			{
				auto view = m_registry.view<RigidBody2DComponent>();
				for (auto e : view)
				{
					Entity entity = { e, this };

					auto& transform = entity.GetComponent<TransformComponent>();
					auto& rigidbody_2d = entity.GetComponent<RigidBody2DComponent>();

					b2Body* body = (b2Body*)rigidbody_2d.runtime_body;
					const auto& position = body->GetPosition();
					transform.m_translation.x = position.x;
					transform.m_translation.y = position.y;
					transform.m_rotation.z = body->GetAngle();
				}
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
			CopyComponentIfExists<CircleRendererComponent>(new_entity, entity);
			CopyComponentIfExists<CameraComponent>(new_entity, entity);
			CopyComponentIfExists<NativeScriptComponent>(new_entity, entity);

			CopyComponentIfExists<RigidBody2DComponent>(new_entity, entity);
			CopyComponentIfExists<BoxCollider2DComponent>(new_entity, entity);
			CopyComponentIfExists<CircleColliderComponent>(new_entity, entity);

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
		void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
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
			class Script : public ScriptableEntity
			{
			public:
				void OnCreate() override {
					m_lua_script->OnCreate();
				}

				void OnUpdate(DeltaTime dt) override {
					m_lua_script->OnUpdate(dt);
				}

				void OnDestroy() override {
					m_lua_script->OnDestroy();
				}
			};

			entity.GetComponent<NativeScriptComponent>().Bind<Script>();
		}

		template<>
		void Scene::OnComponentAdded<RigidBody2DComponent>(Entity entity, RigidBody2DComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<CircleColliderComponent>(Entity entity, CircleColliderComponent& component)
		{
		}

		template<>
		void Scene::OnComponentAdded<EdgeColliderComponent	>(Entity entity, EdgeColliderComponent& component)
		{
		}
	}
}
