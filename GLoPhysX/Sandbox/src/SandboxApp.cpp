#include <iostream>

#include "glophysx.h"
#include "glophysx/core/entry_point.h"

#include "2DExample.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class Sandbox : public Application {
public:
	Sandbox()
	{
		PushLayer(MakeShared<Example2D>());
	}

	~Sandbox()
	{
	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new Sandbox();
}
