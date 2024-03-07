#pragma once

class Font {
public:
	uintptr_t** vtable;
};

class MinecraftGame {
};

class ClientInstance
{
private:
	char pad_0x0000[0xA8];
public:
	MinecraftGame* minecraftGame;  //0xA8

	Actor* getLocalPlayer() {
		return CallVFunc<27, Actor*>(this);
	}
	GuiData* GetGuiData() {
		return *reinterpret_cast<GuiData**>((uintptr_t)this + 0x510);
	}
};