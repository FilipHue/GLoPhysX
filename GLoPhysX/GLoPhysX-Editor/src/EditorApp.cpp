#include <iostream>

#include "glophysx.h"
#include "glophysx/core/entry_point.h"

#include "EditorLayer.h"

class GLoPhysXEditor : public GLOPHYSX::Application {
public:
	GLoPhysXEditor()
	{
		PushLayer(MakeShared<EditorLayer>());
	}

	~GLoPhysXEditor() 
	{
	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new GLoPhysXEditor();
}
