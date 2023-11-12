#include <iostream>

#include "glophysx.h"

class ExampleLayer : public GLOPHYSX::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		//GLOP_CLIENT_INFO("ExampleLayer::Update");
		//GLOP_CLIENT_TRACE("Tab is pressed: {0}", GLOPHYSX::Input::IsKeyPressed(GLOP_KEY_TAB));
	}

	void OnEvent(GLOPHYSX::Event& e) override {
		GLOP_CLIENT_TRACE("{0}", e.ToString())
	}
};

class Sandbox : public GLOPHYSX::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new Sandbox();
}
