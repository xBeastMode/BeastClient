#pragma once

class ModuleManager {
public:
	std::map<ModuleCategory, std::vector<Module*>> module_list;

	void Init() {
		RegisterModule(new Watermark()); //watermark at top for hierarchy

		RegisterModule(new RainbowHotbar());
		RegisterModule(new KeyDisplay());
		RegisterModule(new RainbowFog());
		RegisterModule(new Night());
		RegisterModule(new Zoom());
		RegisterModule(new FPS());
	}

	void RegisterModule(Module* mod) {
		auto modules = module_list.find(mod->category);
		if (modules != module_list.end()) {
			module_list[mod->category].push_back(mod);
		}
		else {
			module_list[mod->category] = {mod};
		}
	}

	Module* getModuleByName(std::string name) {
		for (const auto& pair : module_list) {
			for (Module* mod : pair.second) {
				if (mod->name == name) {
					return mod;
				}
			}
		}
		return nullptr;
	}

	std::vector<Module*> getModulesInCategory(ModuleCategory category) {
		auto modules = module_list.find(category);
		if (modules != module_list.end()) {
			return modules->second;
		}
		return {};
	}

	std::vector<Module*> getAllModules() {
		std::vector<Module*> modules;

		for (const auto& pair : module_list) {
			modules.insert(modules.end(), pair.second.begin(), pair.second.end());
		}

		return modules;
	}

	std::vector<std::string> getAllModuleNames() {
		std::vector<std::string> modules;

		for (const auto& pair : module_list) {
			for (Module* mod : pair.second) {
				modules.push_back(mod->name);
			}
		}

		return modules;
	}

	std::vector<Module*> getAllModulesSortedByName() {
		auto compareModuleByName = [](const Module* s1, const Module* s2) {
			if (s1->name == "Watermark") return true;
			if (s2->name == "Watermark") return false;

			if (s1->name.length() != s2->name.length())
				return (s1->name.length() > s2->name.length());

			return (s1->name < s2->name);
		};

		std::vector<Module*> modules;
		for (const auto& pair : module_list) {
			for (Module* mod : pair.second) {
				modules.push_back(mod);
			}
		}

		std::sort(modules.begin(), modules.end(), compareModuleByName);
		return modules;
	}

	void Delete() {
		for (const auto& pair : module_list) {
			for (Module* mod : pair.second) {
				delete mod;
			}
		}
		module_list.clear();
	}
};