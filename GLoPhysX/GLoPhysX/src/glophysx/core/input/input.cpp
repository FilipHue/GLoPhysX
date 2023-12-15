#include "gxpch.h"

#include "input.h"

#include "platforms/windows/windows_input.h"

namespace GLOPHYSX {

#ifdef GLOP_PLATFORM_WINDOWS
	Unique<Input> Input::s_instance = MakeUnique<WindowsInput>();
#else
	#error "GLoPhysX only supports Windows!"
#endif
}
