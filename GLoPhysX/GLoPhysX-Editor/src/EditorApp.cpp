#include <iostream>

#include "glophysx.h"
#include "glophysx/core/entry_point.h"

#include "EditorLayer.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class GLoPhysXEditor : public Application {
public:
	GLoPhysXEditor() {
		PushLayer(MakeShared<EditorLayer>());
	}

	~GLoPhysXEditor() {

	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new GLoPhysXEditor();
}
