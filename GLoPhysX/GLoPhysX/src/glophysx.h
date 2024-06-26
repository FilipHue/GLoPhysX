#pragma once

/** 
* Main header file to be included by GLoPhysX applications.
* Including this file in an application should be sufficient
* to access all necessary functionality of the GLoPhysX engine.
*/

// Core
#include "glophysx/core/logger/logger.h"
#include "glophysx/core/application/application.h"
#include "glophysx/core/layers/layer.h"
#include "glophysx/core/gui/gui_layer.h" 
#include "glophysx/core/input/input.h"
#include "glophysx/core/input/keycodes.h"
#include "glophysx/core/input/mouse_codes.h"

// Rendering
#include "glophysx/rendering/renderer/renderer.h"
#include "glophysx/rendering/renderer/commands/renderer_commands.h"
#include "glophysx/rendering/renderer/2d/renderer_2d.h"
#include "glophysx/rendering/camera/orthographic/orthographic_camera.h"
#include "glophysx/rendering/camera/orthographic/ortographic_camera_controller.h"
#include "glophysx/rendering/shader/shader.h"
#include "glophysx/rendering/shader/shader_library.h"
#include "glophysx/rendering/objects/texture/texture.h"
#include "glophysx/rendering/objects/buffer/framebuffer/framebuffer.h"
#include "glophysx/rendering/objects/buffer/uniform_buffer/uniform_buffer.h"
#include "glophysx/rendering/objects/buffer/ssbo/shader_strorage_buffer.h"

// Components
#include "glophysx/components/ecs/components.h"
#include "glophysx/components/ecs/entity.h"
#include "glophysx/components/script/scriptable_entity.h"
#include "glophysx/components/scene/scene.h"
#include "glophysx/components/mesh/mesh.h"

#ifdef GLOP_DEBUG
#endif
#include "glophysx/debug/debug.h"
