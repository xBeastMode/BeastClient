#pragma once

#define NOMINMAX
#include <Windows.h>
#include <Psapi.h>
#include <initguid.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_3.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dwrite_1.h>
#include <stdio.h>
#include <string>
#include <bitset>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <d3d11on12.h>
#include <mutex>
#include <DirectXMath.h>
#include <wrl/client.h>

using namespace DirectX;
using namespace Microsoft::WRL;

#include <MinHook.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_win32.h"
#include "include/imgui/imgui_impl_dx11.h"
#include "include/imgui/imgui_impl_dx12.h"

#include "include/kiero/kiero.h"

#include "utils/debug_console.h"
#include "utils/utils.h"
#include "utils/game_addresses.h"

#include "SDK/Vector2.h"
#include "SDK/Vector3.h"
#include "SDK/Vector4.h"
#include "SDK/AABB.h"
#include "SDK/BitmapFont.h"
#include "SDK/TextHolder.h"
#include "SDK/Actor.h"
#include "SDK/UIColor.h"

#include "SDK/CaretMeasureData.h"
#include "SDK/GuiData.h"
#include "SDK/ClientInstance.h"
#include "SDK/MinecraftUIRenderContext.h"

#include "hooks/game_data.h"
#include "utils/color_utils.h"

#include "module/Module.h"
#include "module/modules/FPS.h"
#include "module/modules/KeyDisplay.h"
#include "module/modules/Night.h"
#include "module/modules/RainbowHotbar.h"
#include "module/modules/RainbowFog.h"
#include "module/modules/Watermark.h"
#include "module/modules/Zoom.h"
#include "module/ModuleManager.h"

ModuleManager module_manager;

#include "menu/gui.h"

#include "hooks/game_hooks.h"
#include "hooks/d3d12hook.h"