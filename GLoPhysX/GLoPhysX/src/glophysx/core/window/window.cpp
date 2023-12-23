#include "gxpch.h"

#include "window.h"

namespace GLOPHYSX {

    void Window::SetCallbacks()
    {
        SetWindowCallbacks();
        SetKeyCallbacks();
        SetMouseCallbacks();
    }
}
