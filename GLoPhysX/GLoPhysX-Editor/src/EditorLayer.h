#pragma once

#include "glophysx.h"
#include "panels/scene_hierarchy.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;
using namespace EDITOR;

class EditorLayer : public Layer {
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

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

	glm::vec4 m_square_color = glm::vec4(0.f, 0.f, 0.f, 1.f);

	Shared<Framebuffer> m_framebuffer;

	// Editor
	glm::vec2 m_viewport_size;
	bool m_viewport_focused = true;
	bool m_viewport_hovered = true;

	// Scene
	Shared<Scene> m_current_scene;
	Entity m_square_entity;
	Entity m_main_camera_entity;
	Entity m_second_camera_entity;

	// Panels
	SceneHierarchy m_scene_hierarchy;
};
