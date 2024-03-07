class RainbowFog : public Module {
public:
    RainbowFog() : Module(ModuleCategory::VISUAL, "RainbowFog") {
    }

    void tickRenderContext(MinecraftUIRenderContext* ctx) override {
    }

    void renderImGui() override {
        if (ImGui::CollapsingHeader("Rainbow Fog", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Makes the sky fog smoothly\n change between colors.");
            ImGui::Spacing();
            ImGui::Toggle("Enable Rainbow Fog", &this->enabled);
        }
    }
};