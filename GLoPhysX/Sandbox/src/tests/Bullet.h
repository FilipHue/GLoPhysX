#pragma once

#include "utils/BaseTest.h"

class Bullet : public BaseTest
{
public:
	Bullet();
	~Bullet();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(DeltaTime ts) override;

	void OnGUIRender() override;

	bool OnKeyPress(KeyPressEvent& e) override;
	bool OnMouseScroll(MouseScrollEvent& e) override;

private:
	Entity m_bullet;
};

