#pragma once

#include "npch.h"

// Main Entry Point
#include "core/entry_point.h"

#include "phys/lib.h"

// Compile Time Utility
#include "util/variadics.h"
#include "util/macro.h"
#include "util/hashing.h"

// Core
#include "core/application.h"
#include "core/deltatime.h"
//#include "core/layer.h"

// Serialisation
#include "serial/cereal.h"
#include "serial/serialise.h"

// Events
#include "event/type.h"
#include "event/event.h"
#include "event/window.h"
#include "event/mouse.h"
#include "event/key.h"

// Inputs
#include "input/key.h"
#include "input/mouse.h"
#include "input/poll.h"

// Buffers
#include "render/buffer/buffer.h"
#include "render/buffer/type.h"
#include "render/buffer/context.h"
#include "render/buffer/frame.h"
#include "render/buffer/shader.h"

// Shaders
#include "render/shader.h"

// Textures
#include "render/texture.h"

// Renderer
#include "render/render.h"
#include "render/command.h"
#include "render/draw.h"

// Asset Library
#include "asset/type.h"
#include "asset/resource.h"
#include "asset/stock.h"

// Camera
#include "render/camera.h"
#include "render/camera/ortho.h"
#include "render/camera/perspective.h"

// ECS
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/world.h"
#include "ecs/component/components.h"
#include "ecs/system/systems.h"

// Gui
#include "gui/gui.h"
#include "gui/ext.h"

// Maths Lib
#include "phys/random.h"
