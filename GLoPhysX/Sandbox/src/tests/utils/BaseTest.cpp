#include "BaseTest.h"

static b2Vec2 ConvertScreenToWorld(glm::vec2& point, glm::vec2& screen_size, const glm::mat4& projectionMatrix, const glm::vec3& cameraPos) {
	float ndcX = 2.0f * point.x / screen_size.x - 1.0f;
	float ndcY = 1.0f - 2.0f * point.y / screen_size.y;

	glm::vec4 screenPosNDC(ndcX, ndcY, 0.0f, 1.0f);

	glm::mat4 invProjectionMatrix = glm::inverse(projectionMatrix);

	glm::vec4 worldPos = invProjectionMatrix * screenPosNDC;

	worldPos.x = worldPos.x + cameraPos.x;
	worldPos.y = worldPos.y + cameraPos.y;

	return b2Vec2(worldPos.x, worldPos.y);
}

class QueryCallback : public b2QueryCallback
{
public:
	QueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = nullptr;
	}

	bool ReportFixture(b2Fixture* fixture) override
	{
		b2Body* body = fixture->GetBody();
		b2Vec2 position = body->GetPosition();

		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(m_point);
			if (inside)
			{
				m_fixture = fixture;

				return false;
			}
		}

		return true;
	}

	b2Vec2 m_point;
	b2Fixture* m_fixture;
};

BaseTest::BaseTest() : m_viewport_size(glm::vec2(1600, 900))
{
	m_main_scene = MakeShared<Scene>();
	m_main_scene->OnViewportResize((uint32_t)m_viewport_size.x, (uint32_t)m_viewport_size.y);

	m_ground_point = m_main_scene->CreateEntity("Ground");
	m_ground_point.AddComponent<RigidBody2DComponent>();

	m_camera = m_main_scene->CreateEntity("Camera");
	m_camera.AddComponent<CameraComponent>();
	m_camera.GetComponent<CameraComponent>().m_camera.SetOrthographicSize(9);
	m_camera.GetComponent<CameraComponent>().m_camera.SetZoom(m_camera_zoom);

	m_main_scene->OnRuntimeStart();

	m_world = m_main_scene->GetPhysicsWorld();
}

BaseTest::~BaseTest()
{
}

void BaseTest::OnEvent(Event& e)
{
	EventDispatcher::Dispatch<KeyPressEvent>(e, std::bind(&BaseTest::OnKeyPress, this, std::placeholders::_1));
	EventDispatcher::Dispatch<MouseButtonPressEvent>(e, std::bind(&BaseTest::OnMouseButtonPress, this, std::placeholders::_1));
	EventDispatcher::Dispatch<MouseButtonReleaseEvent>(e, std::bind(&BaseTest::OnMouseButtonRelease, this, std::placeholders::_1));
	EventDispatcher::Dispatch<MouseMoveEvent>(e, std::bind(&BaseTest::OnMouseMove, this, std::placeholders::_1));
	EventDispatcher::Dispatch<MouseScrollEvent>(e, std::bind(&BaseTest::OnMouseScroll, this, std::placeholders::_1));
}

bool BaseTest::OnMouseButtonPress(MouseButtonPressEvent& e)
{
	if (e.GetMouseButton() == GLOP_MOUSE_BUTTON_1) {
		b2Vec2 p = ConvertScreenToWorld(glm::vec2(Input::GetMouseX(), Input::GetMouseY()), m_viewport_size,
			m_camera.GetComponent<CameraComponent>().m_camera.GetProjectionMatrix(),
			m_camera.GetComponent<TransformComponent>().m_translation
		);

		if (m_mouse_joint != nullptr)
		{
			return false;
		}

		b2AABB aabb;
		b2Vec2 d;
		d.Set(0.001f, 0.001f);
		aabb.lowerBound = p - d;
		aabb.upperBound = p + d;

		QueryCallback callback(p);
		m_world->QueryAABB(&callback, aabb);

		if (callback.m_fixture)
		{
			float frequencyHz = 5.0f;
			float dampingRatio = 0.7f;

			b2Body* body = callback.m_fixture->GetBody();
			b2MouseJointDef md;
			md.bodyA = (b2Body*)m_ground_point.GetComponent<RigidBody2DComponent>().runtime_body;
			md.bodyB = body;
			md.target = p;
			md.maxForce = 1000.0f * body->GetMass();

			b2LinearStiffness(md.stiffness, md.damping, frequencyHz, dampingRatio, md.bodyA, md.bodyB);

			m_mouse_joint = (b2MouseJoint*)m_world->CreateJoint(&md);
			body->SetAwake(true);
		}
	}

	return false;
}

bool BaseTest::OnMouseButtonRelease(MouseButtonReleaseEvent& e)
{
	if (e.GetMouseButton() == GLOP_MOUSE_BUTTON_1) {
		if (m_mouse_joint)
		{
			m_world->DestroyJoint(m_mouse_joint);
			m_mouse_joint = nullptr;
		}
	}

	return false;
}

bool BaseTest::OnMouseMove(MouseMoveEvent& e)
{

	if (m_mouse_joint) {
		b2Vec2 p = ConvertScreenToWorld(glm::vec2(Input::GetMouseX(), Input::GetMouseY()), m_viewport_size,
			m_camera.GetComponent<CameraComponent>().m_camera.GetProjectionMatrix(),
			m_camera.GetComponent<TransformComponent>().m_translation
		);

		m_mouse_joint->SetTarget(p);
	}

	return false;
}
