#pragma once

#include "utils/BaseTest.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class VerticalStack: public BaseTest
{
public:
	VerticalStack();
	~VerticalStack();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(DeltaTime ts) override;
	void OnGUIRender() override;

	bool OnKeyPress(KeyPressEvent& e);
	bool OnMouseScroll(MouseScrollEvent& e);

private:
	Entity m_ground;
	Entity m_wall;

	int m_rows;
	int m_columns;
	float m_offsetx[5] = { 0.0f, -0.5f, -1.f, -1.5f, -2.f };
	std::vector<Entity> m_boxes;

	Entity m_bullet;

	float m_scale = 1.f;
};
