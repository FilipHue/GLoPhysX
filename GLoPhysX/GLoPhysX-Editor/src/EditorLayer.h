#pragma once

#include "glophysx.h"
#include "ui/editor_ui.h"
#include "ui/panels/scene_hierarchy.h"
#include "glophysx/rendering/camera/editor/editor_camera.h"

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
	void FileHandler();
	void NewScene();
	void LoadScene();
	void SaveAsScene();

	void ShowGizmos();

	bool OnKeyPress(KeyPressEvent& e);

private:
	Shared<Framebuffer> m_framebuffer;

	// Editor
	EditorCamera m_editor_camera;

	glm::vec2 m_viewport_size;
	bool m_viewport_focused = true;
	bool m_viewport_hovered = true;

	// Editor UI
	EditorUI m_editor_ui;
	int m_gizmo_type = 0;

	// Scene
	Shared<Scene> m_current_scene;
};
