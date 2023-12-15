#pragma once

#include "glophysx/core/input/input.h"

namespace GLOPHYSX {

	class WindowsInput : public Input
	{
	protected:
		bool PIsKeyPressed(int keycode) override;
		bool PIsKeyRepeated(int keycode) override;

		bool PIsMouseButtonPressed(int button) override;
		double PGetMouseX() override;
		double PGetMouseY() override;
	};
}
