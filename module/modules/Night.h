class Night : public Module {
public:
    Night() : Module(ModuleCategory::VISUAL, "Night") {
    }

    void tickRenderContext(MinecraftUIRenderContext* ctx) override {
    }

    void renderImGui() override {
        if (ImGui::CollapsingHeader("Night", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Sets and freezes the time to night.");
            ImGui::Spacing();
            ImGui::Toggle("Enable Night", &this->enabled);
        }
    }
};