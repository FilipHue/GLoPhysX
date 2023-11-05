#include <iostream>

#include "glophysx.h"

class ExampleLayer : public GLOPHYSX::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		GLOP_CLIENT_INFO("ExampleLayer::Update");
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