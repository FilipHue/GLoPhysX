#include "Boxes.h"

Boxes::Boxes()
{
	m_name = "Boxes";
}

Boxes::~Boxes()
{
}

void Boxes::OnAttach()
{
	float wall_size = 25.0f;
	int rows = 26;
	int columns = 5;

	m_wall_left = m_main_scene->CreateEntity("WallLeft");
	m_wall_right = m_main_scene->CreateEntity("WallRight");
	m_wall_bottom = m_main_scene->CreateEntity("WallBottom");

	m_wall_left.AddComponent<RigidBody2DComponent>();
	m_wall_right.AddComponent<RigidBody2DComponent>();
	m_wall_bottom.AddComponent<RigidBody2DComponent>();

	m_wall_left.AddComponent<BoxCollider2DComponent>();
	m_wall_right.AddComponent<BoxCollider2DComponent>();
	m_wall_bottom.AddComponent<BoxCollider2DComponent>();

	m_wall_left.GetComponent<TransformComponent>().m_scale = glm::vec3(wall_size * 2, 1.2f, 1.0f);
	m_wall_right.GetComponent<TransformComponent>().m_scale = glm::vec3(wall_size * 2, 1.2f, 1.0f);
	m_wall_bottom.GetComponent<TransformComponent>().m_scale = glm::vec3(wall_size * 2, 1.2f, 1.0f);

	m_wall_left.GetComponent<TransformComponent>().m_rotation = glm::vec3(0.0f, 0.0f, 0.5f * b2_pi);
	m_wall_right.GetComponent<TransformComponent>().m_rotation = glm::vec3(0.0f, 0.0f, 0.5f * b2_pi);

	m_wall_left.GetComponent<TransformComponent>().m_translation = glm::vec3(-wall_size, wall_size, 0.0f);
	m_wall_right.GetComponent<TransformComponent>().m_translation = glm::vec3(wall_size, wall_size, 1.0f);

	float rad = 0.5f;

	float shift = rad * 2.0f;
	float centerx = shift * rows / 2.0f;
	float centery = shift / 2.0f;

	for (int32_t i = 0; i < rows; ++i)
	{
		float x = i * shift - centerx;

		for (int32_t j = 0; j < columns; ++j)
		{
			float y = j * shift + centery + 2.0f;

			Entity box = m_main_scene->CreateEntity("Box" + i * j);
			box.AddComponent<RigidBody2DComponent>();
			box.AddComponent<BoxCollider2DComponent>();

			box.GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
			box.GetComponent<TransformComponent>().m_translation = glm::vec3(x, y, 0.0f);
		}
	}

	m_main_scene->OnRuntimeStart();

	m_world = m_main_scene->GetPhysicsWorld();
}

void Boxes::OnDetach()
{
}

void Boxes::OnUpdate(DeltaTime ts)
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

void Boxes::OnGUIRender()
{
}

bool Boxes::OnKeyPress(KeyPressEvent& e)
{
    return false;
}

bool Boxes::OnMouseScroll(MouseScrollEvent& e)
{
	m_camera_zoom -= e.GetYOffset() * 0.01f;
	m_main_scene->GetPrimaryCameraEntity().GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	return false;
}
