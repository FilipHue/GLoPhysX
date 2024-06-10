#pragma once

#include "utils/BaseTest.h"

class Pyramid : public BaseTest
{
public:
	Pyramid();
	~Pyramid();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(DeltaTime ts) override;

	void OnGUIRender() override;

	bool OnKeyPress(KeyPressEvent& e) override;
	bool OnMouseScroll(MouseScrollEvent& e) override;

private:
	Entity m_ground;
};

