#include <iostream>

#include "glophysx.h"
#include "glophysx/core/entry_point.h"

#include "EditorLayer.h"

class GLoPhysXEditor : public GLOPHYSX::Application
{
public:
	GLoPhysXEditor(const GLOPHYSX::ApplicationSpecifications& spec) : Application(spec)
	{
		PushLayer(MakeShared<EditorLayer>());
	}

	~GLoPhysXEditor() 
	{
	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication(CommandLineArgs args)
{
	GLOPHYSX::ApplicationSpecifications spec;
	spec.m_name = "GLOPHYSX ENGINE";
	spec.m_width = 1600;
	spec.m_height = 900;

	/*std::string exe_path = std::string(args[0]);
	std::string current_dir = exe_path.substr(0, exe_path.find_last_of("/\\"));
	spec.m_working_directory = current_dir;*/

	return new GLoPhysXEditor(spec);
}
