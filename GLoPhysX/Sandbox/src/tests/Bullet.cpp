#include "Bullet.h"

#define	RAND_LIMIT 32767

inline static float RandomFloat(float lo, float hi)
{
	float r = (float)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}

Bullet::Bullet()
{
	m_name = "Bullet";
}

Bullet::~Bullet()
{
}

void Bullet::OnAttach()
{
	m_camera_zoom = 3.0f;

	m_bullet = m_main_scene->CreateEntity("Bullet");
	m_bullet.AddComponent<RigidBody2DComponent>();
	m_bullet.AddComponent<BoxCollider2DComponent>();
	m_bullet.GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
	m_bullet.GetComponent<RigidBody2DComponent>().is_bullet = true;
	m_bullet.GetComponent<RigidBody2DComponent>().linear_velocity = glm::vec2(10.0f, 0.0f);
	m_bullet.GetComponent<TransformComponent>().m_scale = glm::vec3(1.5f, 1.5f, 1.0f);
	m_bullet.GetComponent<TransformComponent>().m_translation = glm::vec3(-10.0f, 0.0f, 0.0f);

	float minX = 3.0f;
	float maxX = 6.0f;
	float minY = 2.0f;
	float maxY = -2.0f;

	for (int32 i = 0; i < 400; ++i)
	{
		Entity object = m_main_scene->CreateEntity("Circle" + i);
		object.AddComponent<RigidBody2DComponent>();
		object.AddComponent<CircleColliderComponent>();

		object.GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
		object.GetComponent<CircleColliderComponent>().radius = 0.1f;
		object.GetComponent<CircleColliderComponent>().density = 0.01f;
		object.GetComponent<TransformComponent>().m_translation = glm::vec3(RandomFloat(minX, maxX), RandomFloat(minY, maxY), 0.0f);
	}

	m_camera.GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	m_main_scene->OnRuntimeStart();

	m_world = m_main_scene->GetPhysicsWorld();
	m_world->SetGravity({ 0.0f, 0.0f });
}

void Bullet::OnDetach()
{
}

void Bullet::OnUpdate(DeltaTime ts)
{
	RendererCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RendererCommands::Clear();

	Renderer2D::ResetStats();

	m_main_scene->OnUpdateRuntime(ts);

	float move_speed = 0.07f * m_camera_zoom;
	if (Input::IsKeyPressed(GLOP_KEY_A)) {
		m_main_scene->GetPrimaryCameraEntity().GetComponent<TransformComponent>().m_translation -= glm::vec3(move_speed, 0.0f, 0.0f);
	}
	if (Input::IsKeyPressed(GLOP_KEY_D)) {
		m_main_scene->GetPrimaryCameraEntity().GetComponent<TransformComponent>().m_translation += glm::vec3(move_speed, 0.0f, 0.0f);
	}
	if (Input::IsKeyPressed(GLOP_KEY_W)) {
		m_main_scene->GetPrimaryCameraEntity().GetComponent<TransformComponent>().m_translation += glm::vec3(0.0f, move_speed, 0.0f);
	}
	if (Input::IsKeyPressed(GLOP_KEY_S)) {
		m_main_scene->GetPrimaryCameraEntity().GetComponent<TransformComponent>().m_translation -= glm::vec3(0.0f, move_speed, 0.0f);
	}
}

void Bullet::OnGUIRender()
{
}

bool Bullet::OnKeyPress(KeyPressEvent& e)
{
    return false;
}

bool Bullet::OnMouseScroll(MouseScrollEvent& e)
{
	m_camera_zoom -= e.GetYOffset() * 0.01f;
	m_main_scene->GetPrimaryCameraEntity().GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	return false;
}
