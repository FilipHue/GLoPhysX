#include "Pyramid.h"

Pyramid::Pyramid()
{
	m_name = "Pyramid";
}

Pyramid::~Pyramid()
{
}

void Pyramid::OnAttach()
{
	m_ground = m_main_scene->CreateEntity("Ground");
	m_ground.AddComponent<RigidBody2DComponent>();
	m_ground.AddComponent<EdgeColliderComponent>();
	m_ground.GetComponent<TransformComponent>().m_scale = glm::vec3(100.0f, 1.0f, 1.0f);

	srand(NULL);
	float a = 0.5f;

	b2Vec2 x(-7.0f, 0.75f);
	b2Vec2 y;
	b2Vec2 deltaX(0.5625f, 1.25f);
	b2Vec2 deltaY(1.125f, 0.0f);

	for (int32 i = 0; i < 20; ++i)
	{
		y = x;

		for (int32 j = i; j < 20; ++j)
		{
			Entity box = m_main_scene->CreateEntity("Box2" + i * j);
			box.AddComponent<RigidBody2DComponent>();
			//box.AddComponent<SpriteComponent>();
			box.AddComponent<BoxCollider2DComponent>();
			box.GetComponent<RigidBody2DComponent>().type = BodyType::DYNAMIC;
			box.GetComponent<BoxCollider2DComponent>().size = glm::vec2(a, a);
			box.GetComponent<BoxCollider2DComponent>().density = 5.0f;
			box.GetComponent<TransformComponent>().m_translation = glm::vec3(y.x, y.y, 0.0f);
			y += deltaY;
		}

		x += deltaX;
	}

	m_main_scene->OnRuntimeStart();

	m_world = m_main_scene->GetPhysicsWorld();

	//// TO DO
	//// We cannot add more than 1 fixture to a rigidbody2d component
	//{
	//	float a = 0.5f;
	//	b2BodyDef bd;
	//	bd.position.y = -a;
	//	b2Body* ground = m_world->CreateBody(&bd);

	//	int32 N = 200;
	//	int32 M = 10;
	//	b2Vec2 position;
	//	position.y = 0.0f;
	//	for (int32 j = 0; j < M; ++j)
	//	{
	//		position.x = -N * a;
	//		for (int32 i = 0; i < N; ++i)
	//		{
	//			b2PolygonShape shape;
	//			shape.SetAsBox(a, a, position, 0.0f);
	//			ground->CreateFixture(&shape, 0.0f);
	//			position.x += 2.0f * a;
	//		}
	//		position.y -= 2.0f * a;
	//	}
	//}
}

void Pyramid::OnDetach()
{
}

void Pyramid::OnUpdate(DeltaTime ts)
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

void Pyramid::OnGUIRender()
{
}

bool Pyramid::OnKeyPress(KeyPressEvent& e)
{
	return false;
}

bool Pyramid::OnMouseScroll(MouseScrollEvent& e)
{
	m_camera_zoom -= e.GetYOffset() * 0.01f;
	m_main_scene->GetPrimaryCameraEntity().GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	return false;
}
