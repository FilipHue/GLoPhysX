#include "VerticalStack.h"

VerticalStack::VerticalStack()
{
	m_name = "VerticalStack";

	m_rows = 7;
	m_columns = 3;
}

VerticalStack::~VerticalStack()
{
}

void VerticalStack::OnAttach()
{	
	m_camera_zoom = 1.0f;

	m_ground = m_main_scene->CreateEntity("Ground");
	m_ground.AddComponent<RigidBody2DComponent>();
	m_ground.AddComponent<EdgeColliderComponent>();
	m_ground.GetComponent<TransformComponent>().m_translation = glm::vec3(0.0f, -1.0f * m_scale, 0.0f);
	m_ground.GetComponent<TransformComponent>().m_scale = glm::vec3(8.f * m_scale, 1.0 * m_scale, 1.0f);

	m_wall = m_main_scene->CreateEntity("Wall");
	m_wall.AddComponent<RigidBody2DComponent>();
	m_wall.AddComponent<EdgeColliderComponent>();
	m_wall.GetComponent<EdgeColliderComponent>().start = glm::vec2(0.0f, 0.0f);
	m_wall.GetComponent<EdgeColliderComponent>().stop = glm::vec2(0.0f, 0.5f);
	m_wall.GetComponent<TransformComponent>().m_translation = glm::vec3(2.0f * m_scale, -1.0f * m_scale, 0.0f);
	m_wall.GetComponent<TransformComponent>().m_scale = glm::vec3(8.0f * m_scale, 8.0f * m_scale, 0.0f);

	for (int i = 0; i < m_columns; i++) {
		for (int j = 0; j < m_rows; j++) {
			m_boxes.push_back(m_main_scene->CreateEntity("Box" + i * j));
			m_boxes[i * m_rows + j].AddComponent<RigidBody2DComponent>();
			m_boxes[i * m_rows + j].AddComponent<BoxCollider2DComponent>();
			m_boxes[i * m_rows + j].GetComponent<TransformComponent>().m_scale = glm::vec3(0.25f * m_scale, 0.25f * m_scale, 1.0f);
			m_boxes[i * m_rows + j].GetComponent<TransformComponent>().m_translation = glm::vec3(m_offsetx[i] * m_scale, 0.25f * (j + 1) * m_scale, 1.0f);
			m_boxes[i * m_rows + j].GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
		}
	}

	m_camera.GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	m_main_scene->OnRuntimeStart();

	m_world = m_main_scene->GetPhysicsWorld();
}

void VerticalStack::OnDetach()
{
	m_main_scene->OnRuntimeShutdown();
}

void VerticalStack::OnUpdate(DeltaTime ts)
{
	RendererCommands::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
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

void VerticalStack::OnGUIRender()
{
}

bool VerticalStack::OnKeyPress(KeyPressEvent& e)
{
	if (e.GetKeycode() == GLOP_KEY_ENTER) {
		m_main_scene->DestroyEntity(m_bullet);

		m_bullet = m_main_scene->CreateEntity("Bullet");
		m_bullet.AddComponent<RigidBody2DComponent>();
		m_bullet.AddComponent<CircleColliderComponent>();
		m_bullet.GetComponent<TransformComponent>().m_scale = glm::vec3(0.25f * m_scale, 0.25f * m_scale, 1.0f);
		m_bullet.GetComponent<TransformComponent>().m_translation = glm::vec3(-3.0f * m_scale, 0.5f * m_scale, 1.0f);
		m_bullet.GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
		m_bullet.GetComponent<RigidBody2DComponent>().linear_velocity = glm::vec2(15.0f * m_scale, 0.0f);
		m_bullet.GetComponent<CircleColliderComponent>().density = 20.0f;

		m_main_scene->OnRuntimeStart();

		m_world = m_main_scene->GetPhysicsWorld();
	}

	return false;
}

bool VerticalStack::OnMouseScroll(MouseScrollEvent& e)
{
	m_camera_zoom -= e.GetYOffset() * 0.01f;
	m_camera_zoom = std::clamp(m_camera_zoom, 0.01f, 10.0f);
	m_main_scene->GetPrimaryCameraEntity().GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	return false;
}
