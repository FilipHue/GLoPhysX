#pragma once

#include "glophysx.h"

#include "glophysx/rendering/camera/editor/editor_camera.h"

#include "ui/editor_ui.h"

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
	void MenuBar();

	void FileHandler();
	void FileHandlerInput(KeyPressEvent& e);
	void NewScene();
	void LoadScene();
	void LoadScene(const std::filesystem::path& path);
	void SaveScene();
	void SaveAsScene();

	void Options();
	void EditorCameraOptions();

	void DuplicateEntity();

	void GizmosInput(KeyPressEvent& e);
	void ShowGizmos();
	void DebugUtils();

	bool OnKeyPress(KeyPressEvent& e);
	bool OnMouseButtonPress(MouseButtonPressEvent& e);

private:
	Shared<Framebuffer> m_framebuffer;
	glm::vec2 m_viewport_bounds[2];

	// Editor
	EditorCamera m_editor_camera;
	bool m_show_editor_camera_properties = false;

	glm::vec2 m_viewport_size;
	bool m_viewport_focused = true;
	bool m_viewport_hovered = true;

	int m_selected_entity;

	// Editor UI
	EditorUI m_editor_ui;
	int m_gizmo_type = 0;
	bool m_show_colliders = 0;

	// Scene
	Shared<Scene> m_current_scene;
	Shared<Scene> m_editor_scene, m_runtime_scene;
	std::string m_save_path = std::string("assets/scenes");

	// Other
	Entity m_square;
	Entity m_camera;
};
