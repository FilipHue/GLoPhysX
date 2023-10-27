#pragma once

#include "core.h"

namespace GLOPHYSX {

	class GLOP_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}
