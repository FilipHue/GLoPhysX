#pragma once

#include "glophysx.h"

#include "box2d/b2_settings.h"

#include "box2d/b2_polygon_shape.h"

#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

#include "box2d/b2_mouse_joint.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class BaseTest: public Layer
{
public:
	BaseTest();
	virtual ~BaseTest();

	virtual void OnAttach() {};
	virtual void OnDetach() {};

	virtual void OnUpdate(DeltaTime ts) {};
	virtual void OnGUIRender() {};
	virtual void OnEvent(Event& e);

	virtual bool OnMouseButtonPress(MouseButtonPressEvent& e);
	virtual bool OnMouseButtonRelease(MouseButtonReleaseEvent& e);
	virtual bool OnMouseMove(MouseMoveEvent& e);

	virtual bool OnKeyPress(KeyPressEvent& e) { return false; }
	virtual bool OnMouseScroll(MouseScrollEvent& e) { return false; }

	const char* GetName() { return m_name; }

protected:
	glm::vec2 m_viewport_size;

	Shared<Scene> m_main_scene;

	Entity m_camera;
	float m_camera_zoom = 5.f;

	Entity m_ground_point;

	b2MouseJoint* m_mouse_joint = nullptr;
	b2World* m_world;

	const char* m_name = "BaseTest";
};
