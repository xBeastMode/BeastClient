#pragma once

static uintptr_t MinecraftUIRenderContextAddress;
static uintptr_t MouseUpdateCallbackAddress;
static uintptr_t DrawTextCallbackAddress;
static uintptr_t KeyStrokeCallbackAddress;
static uintptr_t FillRectangleCallbackAddress;
static uintptr_t FOVCallbackAddress;
static uintptr_t FOVAddress;
static uintptr_t FOGColorCallbackAddress;
static uintptr_t TimeCallbackAddress;
static uintptr_t MinecraftUIRenderContext_DrawImageAddress;

void InitAddresses() {
	MinecraftUIRenderContextAddress = FindSig("48 8B ? 48 89 ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? 4C 8B ? 48 89 ? ? ? 4C 8B");
	MouseUpdateCallbackAddress = FindSig("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24");
	DrawTextCallbackAddress = FindSig("? ? ? ? ? 55 56 57 48 83 EC 70 4C 8B 94 24 ? ? ? ? 48 8D 84 24 ? ? ? ?");
	KeyStrokeCallbackAddress = FindSig("48 83 ? ? ? B6 C1 4C 8D 05 ? ? ? ? 89 54 24 20 88 4C 24 24 41 89 14 80");
	FillRectangleCallbackAddress = FindSig("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 60 ? ? 74 24 50 49 8B D8 ? ? F3 48 8B FA 48 8B F1 E8 ? ? ? ? F3 ? ? 03 48 8D 44 24 40");
	FOVCallbackAddress = FindSig("48 8B C4 48 89 58 18 48 89 70 20 57 48 81 EC ? ? ? ? ? ? 70 E8 ? ? 78 D8 44 ? ? 40 C8 44 ? ? 48 B8 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 48 41 ? ? F0");
	FOGColorCallbackAddress = FindSig("41 0F 10 08 48 8B C2 0F");
	TimeCallbackAddress = FindSig("44 8B C2 B8 ? ? ? ? F7 EA");
	MinecraftUIRenderContext_DrawImageAddress = FindSig("48 8B C4 48 89 58 10 48 89 68 18 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? ? ? 70 C8 ? ? 78 B8 48 8B 05 ? ? ? ?");

	std::cout << FOGColorCallbackAddress << std::endl;
;}