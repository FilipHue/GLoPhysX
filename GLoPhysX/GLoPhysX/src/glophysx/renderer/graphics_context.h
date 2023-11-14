#pragma once

namespace GLOPHYSX {

	namespace RENDERER {

		class GraphicsContext
		{
		public:
			virtual ~GraphicsContext() = default;

			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
			virtual void Destroy() = 0;

			static std::unique_ptr<GraphicsContext> Create(void* window);
		};
	}
}
