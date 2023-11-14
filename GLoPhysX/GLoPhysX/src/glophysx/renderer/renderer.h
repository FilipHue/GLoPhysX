#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {
	
	namespace RENDERER {

		GLOP_API enum class API {
			NONE,
			OPENGL
		};

		class RendererAPI {
		public:
			GLOP_API inline static API GetApi() { return s_API; }
			GLOP_API inline static void SetApi(API graphics_api) { s_API = graphics_api; }

		private:
			static API s_API;
		};
	}
}