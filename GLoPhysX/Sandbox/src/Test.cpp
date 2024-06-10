#include "Test.h"

#include "imgui.h"

Test::Test()
{
}

Test::~Test()
{
}

void Test::OnAttach()
{
	m_test_names[0] = "Boxes";
	m_test_names[1] = "Bullet";
	m_test_names[2] = "Pyramid";
	m_test_names[3] = "VerticalStack";

	m_current_test = new Boxes();
	m_current_test->OnAttach();
}

void Test::OnDetach()
{
	m_current_test->OnDetach();

}

void Test::OnUpdate(DeltaTime ts)
{
	m_current_test->OnUpdate(ts);
}

void Test::OnGUIRender()
{
	float menu_width = 180.0f;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos + ImVec2(viewport->Size.x - menu_width - 10.0f, 10.0f));
	ImGui::SetNextWindowSize(viewport->Size - ImVec2(viewport->Size.x - menu_width, 20.0f));

	ImGui::Begin("Tests", &m_show_ui, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGuiTreeNodeFlags leafNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	leafNodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	int i = 0;
	while (i < m_no_tests) {
		ImGuiTreeNodeFlags selectionFlags = 0;
		ImGui::TreeNodeEx((void*)(intptr_t)i, leafNodeFlags, "%s", m_test_names[i]);
		if (ImGui::IsItemClicked())
		{
			delete m_current_test;
			
			if (i == 0) {
				m_current_test = new Boxes();
			}
			else if (i == 1) {
				m_current_test = new Bullet();
			}
			else if (i == 2) {
				m_current_test = new Pyramid();
			}
			else if (i == 3) {
				m_current_test = new VerticalStack();
			}

			m_current_test->OnAttach();
		}
		++i;
	}

	ImGui::End();
}

void Test::OnEvent(Event& e)
{
	m_current_test->OnEvent(e);
}
