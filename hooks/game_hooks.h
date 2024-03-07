#pragma once

static bool zoomEnabled = false;
static long ticks = 0;

static bool init = false;

static std::mutex mux;

bool isZoomEnabled() {
	return dynamic_cast<Zoom*>(module_manager.getModuleByName("Zoom"))->enabled;
}

bool isNightEnabled() {
	return dynamic_cast<Night*>(module_manager.getModuleByName("Night"))->enabled;
}

bool isRainbowFogEnabled() {
	return dynamic_cast<RainbowFog*>(module_manager.getModuleByName("RainbowFog"))->enabled;
}

bool isRainbowHotbarEnabled() {
	return dynamic_cast<RainbowHotbar*>(module_manager.getModuleByName("RainbowHotbar"))->enabled;
}

typedef void(*MinecraftUIRenderContextCallback)(uintptr_t, MinecraftUIRenderContext*);
MinecraftUIRenderContextCallback oRenderContext;

void MinecraftUIRenderContextHook(uintptr_t thisptr, MinecraftUIRenderContext* ctx) {
	if (ctx->ClientInstance != nullptr) {
		if (ctx->ClientInstance->GetGuiData() != nullptr) {
			guiData = ctx->ClientInstance->GetGuiData();
		}
		if (ctx->ClientInstance->getLocalPlayer() != nullptr) {
			localPlayer = ctx->ClientInstance->getLocalPlayer();
		}
		else {
			localPlayer = nullptr;
		}
		clientInstance = ctx->ClientInstance;
	}

	if (drawImGui) {
		return;
	}

	auto lock = std::lock_guard(mux);

	optr = thisptr;
	oContext = ctx;

	RenderMinecraftUI(oContext);
	oRenderContext(optr, oContext);
}

typedef __int64(*MouseUpdateCallback)(__int64 a1, char a2, char a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, char a8);
MouseUpdateCallback oMouseUpdate;

__int64 MouseUpdateHooked(__int64 a1, char a2, char a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, char a8) {
	if (a2 == 1 || a2 == 2) {
		keyMap[a2] = a3;
	}

	if (a2 == 0) {
		if (_moves % 5 == 0 && moves < 10) {
			moves++;
		}
		_moves++;
	}

	if (ImGui::GetCurrentContext() != nullptr) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(a4, a5);

		switch (a2) {
		case 1:
			io.MouseDown[0] = a3;
			break;
		case 2:
			io.MouseDown[1] = a3;
			break;
		case 3:
			io.MouseDown[2] = a3;
			break;
		case 4:
			io.MouseWheel = a3 < 0 ? -0.5f : 0.5f;
			break;
		default:
			break;
		}

		if (!io.WantCaptureMouse) return oMouseUpdate(a1, a2, a3, a4, a5, a6, a7, a8);

	}

	if (drawImGui) {
		return 0;
	}

	return oMouseUpdate(a1, a2, a3, a4, a5, a6, a7, a8);
}

typedef __int64(*DrawTextCallback)(void*, Font& font, const Vector4&, TextHolder&, UIColor&, float, unsigned int, TextMeasureData&, const CaretMeasureData&);
DrawTextCallback oDrawText;

__int64 DrawTextHooked(void* ptr, Font& font, const Vector4& pos, TextHolder& text, UIColor& color, float alpha, unsigned int textAlignment, TextMeasureData& textMeasureData, const CaretMeasureData& caretMeasureData) {
	std::cout << "a2";
	if (oFont == nullptr) oFont = &font;
	return oDrawText(ptr, font, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
}

typedef void(*KeyStrokeCallback)(__int32 key, bool  held);
KeyStrokeCallback oKeyStroke;

void KeyStrokeHooked(__int32 key, bool held) {
	if (key == VK_INSERT && held) {
		drawImGui = !drawImGui;
		ImGui::SetWindowFocus();

		if (localPlayer != nullptr) {
			oKeyStroke(VK_ESCAPE, true);
		}
	}

	if (drawImGui) {
		return;
	}

	if (key == VK_DELETE && held) {
		running = false;
	}
	if (isZoomEnabled() && key == 0x43) {
		zoomEnabled = !zoomEnabled;
	}
	keyMap[key] = held;
	oKeyStroke(key, held);
}

typedef void(*FillRectangleCallback)(void*, const Vector4&, UIColor&, float);
FillRectangleCallback oFillRectangle;

void FillRectangleHooked(void* ptr, const Vector4& pos, UIColor& color, float alpha) {
	oFillRectangle(ptr, pos, color, alpha);
}

typedef float (__fastcall* FOVCallback)(__int64, float, bool);
FOVCallback oFOV;

float __fastcall FOVHooked(__int64 a1, float f, bool a3) {
	if (!isZoomEnabled()) {
		zoomEnabled = false;
	}

	float fov = oFOV(a1, f, a3);
	constexpr float zoomValue = 0.75f;
	static float animValue = 0.0f;
	if (zoomEnabled) {
		animValue = std::min(animValue + (f * 0.1f), 1.0f);
	}
	else {
		animValue = std::max(animValue - (f * 0.1f), 0.0f);
	}

	fov -= (animValue * animValue * zoomValue * fov);
	return std::min(std::max(fov, 1.0f), 179.0f);
}

typedef float* (*FogColorCallback)(void*, float*, __int64, float);
FogColorCallback oFog;

float* FogColorHooked(void* ptr, float* color, __int64 a3, float a4) {
	if (isRainbowFogEnabled()) {
		UIColor co = ColorUtils::getRainbow(6, 1, 1);

		color[0] = co.r;
		color[1] = co.g;
		color[2] = co.b;
		color[3] = co.a;

		return color;
	}
	return oFog(ptr, color, a3, a4);
}

typedef float (*TimeCallback)(void*, int, float);
TimeCallback oTime;

float TimeHooked(void* ptr, int a2, float a3) {
	if (isNightEnabled()) {
		return 0.5;
	}
	return oTime(ptr, a2, a3);
}

typedef __int64(__fastcall* MinecraftUIRenderContext_DrawImageCallback)(MinecraftUIRenderContext*, __int64, const Vector2&, const Vector2&, void*, void*);
MinecraftUIRenderContext_DrawImageCallback oDrawImage;

int idx = 0;

__int64 __fastcall MinecraftUIRenderContext_DrawImageHooked(MinecraftUIRenderContext* ctx, __int64 a3, const Vector2& a4, const Vector2& a5, void* a6, void* a7) {
	if (isRainbowHotbarEnabled()) {
		if (a5.x == 20 && a5.y == 22) {
			oContext->fillRectangle(Vector4(a4, Vector2(a5.x, 2)), ColorUtils::getRainbow(6, 1, 1), 1);
			return 0;
		}

		if (a5.x == 24 && a5.y == 24) {
			oContext->fillRectangle(Vector4(Vector2(a4.x, a4.y + a5.y - 1), Vector2(a5.x, 2)), ColorUtils::getRainbow(6, 1, 1), 1);
			return 0;
		}
	}

	float div = a5.x / a5.y;

	/*std::cout << div << std::endl;
	std::cout << (oContext != nullptr) << std::endl;
	std::cout << (oFont != nullptr) << std::endl;*/

	if (div > 5 && div < 6 && oContext != nullptr && oFont != nullptr) {
		Vector2 pos = a4;
		int index = 0;
		for (std::string pz : logo) {
			TextHolder text = TextHolder(pz);
			DrawMinecraftText(Vector4(pos, a5), text, ColorUtils::getRainbow(6, 1, 1, index * 100), div, 1);
			pos.x += oContext->getLineLength(*oFont, text, div, false);
			++index;
		}
		return 0;
	}
	
	return oDrawImage(ctx, a3, a4, a5, a6, a7);
}

void InitGameHooks() {
	if (MH_Initialize() == MH_OK) {
		if (MH_CreateHook((void*)MinecraftUIRenderContextAddress, &MinecraftUIRenderContextHook, reinterpret_cast<LPVOID*>(&oRenderContext)) == MH_OK) {
			MH_EnableHook((void*)MinecraftUIRenderContextAddress);
		}

		if (MH_CreateHook((void*)MouseUpdateCallbackAddress, &MouseUpdateHooked, reinterpret_cast<LPVOID*>(&oMouseUpdate)) == MH_OK) {
			MH_EnableHook((void*)MouseUpdateCallbackAddress);
		}

		if (MH_CreateHook((void*)DrawTextCallbackAddress, &DrawTextHooked, reinterpret_cast<LPVOID*>(&oDrawText)) == MH_OK) {
			MH_EnableHook((void*)DrawTextCallbackAddress);
		}

		if (MH_CreateHook((void*)KeyStrokeCallbackAddress, &KeyStrokeHooked, reinterpret_cast<LPVOID*>(&oKeyStroke)) == MH_OK) {
			MH_EnableHook((void*)KeyStrokeCallbackAddress);
		}

		if (MH_CreateHook((void*)FOVCallbackAddress, &FOVHooked, reinterpret_cast<LPVOID*>(&oFOV)) == MH_OK) {
			MH_EnableHook((void*)FOVCallbackAddress);
		}

		if (MH_CreateHook((void*)FOGColorCallbackAddress, &FogColorHooked, reinterpret_cast<LPVOID*>(&oFog)) == MH_OK) {
			MH_EnableHook((void*)FOGColorCallbackAddress);
		}

		if (MH_CreateHook((void*)TimeCallbackAddress, &TimeHooked, reinterpret_cast<LPVOID*>(&oTime)) == MH_OK) {
			MH_EnableHook((void*)TimeCallbackAddress);
		}

		if (MH_CreateHook((void*)MinecraftUIRenderContext_DrawImageAddress, &MinecraftUIRenderContext_DrawImageHooked, reinterpret_cast<LPVOID*>(&oDrawImage)) == MH_OK) {
			MH_EnableHook((void*)MinecraftUIRenderContext_DrawImageAddress);
		}

		if (MH_CreateHook((void*)FillRectangleCallbackAddress, &FillRectangleHooked, reinterpret_cast<LPVOID*>(&oFillRectangle)) == MH_OK) {
			MH_EnableHook((void*)FillRectangleCallbackAddress);
		}
	}
}