#pragma once

#include "TestsEntries.h"
#include "tests/utils/BaseTest.h"

class Test : public Layer
{
public:
	Test();
	~Test();

	virtual void OnAttach();
	virtual void OnDetach();

	virtual void OnUpdate(DeltaTime ts);
	virtual void OnGUIRender();
	virtual void OnEvent(Event& e);

private:
	BaseTest* m_current_test;

	static const int m_no_tests = 4;
	std::unordered_map<int, const char*> m_test_names;

	glm::vec2 m_viewport_size;
	bool m_show_ui = true;
};
