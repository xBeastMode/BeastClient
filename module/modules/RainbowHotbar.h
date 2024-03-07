class RainbowHotbar : public Module {
public:
    RainbowHotbar() : Module(ModuleCategory::VISUAL, "RainbowHotbar") {
    }

    void tickRenderContext(MinecraftUIRenderContext* ctx) override {
    }

    void renderImGui() override {
        if (ImGui::CollapsingHeader("Rainbow Hotbar", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Makes your hotbar transparent and rainbow.");
            ImGui::Spacing();
            ImGui::Toggle("Enable Rainbow Hotbar", &this->enabled);
        }
    }
};