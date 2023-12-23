#pragma once

#include "glophysx.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class Example2D : public Layer {
public:
	Example2D();
	virtual ~Example2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(DeltaTime ts) override;
	void OnGUIRender() override;
	void OnEvent(Event& e) override;

private:
	Shared<OrthographicCameraController> m_camera_controller;

	Unique<Mesh> m_square;
	Shared<Texture2D> m_checkerboard;
	Unique<ShaderLibrary> m_shader_library;

	glm::vec4 m_square_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};
