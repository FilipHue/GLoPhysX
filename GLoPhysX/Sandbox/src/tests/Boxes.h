#pragma once

#include "utils/BaseTest.h"

class Boxes : public BaseTest
{
public:
	Boxes();
	~Boxes();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(DeltaTime ts) override;

	void OnGUIRender() override;

	bool OnKeyPress(KeyPressEvent& e) override;
	bool OnMouseScroll(MouseScrollEvent& e) override;

private:
	Entity m_wall_left;
	Entity m_wall_right;
	Entity m_wall_bottom;
};

