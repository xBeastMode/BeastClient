#pragma once

enum ModuleCategory {
	VISUAL
};

class Module {
public:
	Module(ModuleCategory category = ModuleCategory::VISUAL, std::string name = "null", std::string description = "", std::string tooltip = "null", uintptr_t keybind = 0x0, bool enabled = true) {
		this->category = category;
		this->name = name;
		this->description = description;
		this->tooltip = tooltip;
		this->keybind = keybind;
		this->enabled = enabled;
	};

public:
	ModuleCategory category;
	std::string name;
	std::string description;
	std::string tooltip;
	uintptr_t keybind;
	bool enabled;

	virtual void tickRenderContext(MinecraftUIRenderContext* ctx){}
	virtual void renderImGui() {}
	virtual void renderAutonomousImGui() {}
};