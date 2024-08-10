#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>

#define IMGUI_DEFINE_MATH_OPERATORS

#define PROCESS_NAME "explorer.exe"

#include <dma/Memory/Memory.h>
#include <imgui/imgui.h>

#include "./Misc/Math/Math.hpp"
#include "./Globals.hpp"
#include "./Misc/Security/Safe.hpp"
#include "Config/Config.hpp"

#include "./Misc/Input/Input.hpp"
#include "./Window/Renderer/Renderer.hpp"