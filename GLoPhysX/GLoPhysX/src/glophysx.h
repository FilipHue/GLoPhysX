#pragma once

/** 
* Main header file to be included by GLoPhysX applications.
* Including this file in an application should be sufficient
* to access all necessary functionality of the GLoPhysX engine.
*/

#include "glophysx/core/application/application.h"
#include "glophysx/core/logger/logger.h"

#include "glophysx/core/layers/layer.h"
#include "glophysx/core/gui/gui_layer.h" 

#include "glophysx/core/input/input.h"
#include "glophysx/core/input/keycodes.h"
#include "glophysx/core/input/mouse_codes.h"

#include "glophysx/rendering/renderer/renderer.h"
#include "glophysx/rendering/renderer/commands/renderer_commands.h"

#include "glophysx/rendering/camera/orthographic/orthographic_camera.h"

#include "glophysx/rendering/shader/shader.h"

#include "glophysx/rendering/components/mesh/mesh.h"

#include "glophysx/core/entry_point.h"
