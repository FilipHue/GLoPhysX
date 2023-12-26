#include <iostream>

#include "glophysx.h"
#include "glophysx/core/entry_point.h"

#include "2DExample.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class Sandbox : public Application {
public:
	Sandbox(const GLOPHYSX::ApplicationSpecifications& spec) : Application(spec)
	{
		PushLayer(MakeShared<Example2D>());
	}

	~Sandbox()
	{
	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication(CommandLineArgs args) {
	GLOPHYSX::ApplicationSpecifications spec;
	spec.m_name = "GLOPHYSX ENGINE";
	spec.m_width = 1600;
	spec.m_height = 900;

	/*std::string exe_path = std::string(args[0]);
	std::string current_dir = exe_path.substr(0, exe_path.find_last_of("/\\"));
	spec.m_working_directory = current_dir;*/

	return new Sandbox(spec);
}
