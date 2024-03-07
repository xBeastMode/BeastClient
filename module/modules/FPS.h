class FPS : public Module {
public:
    FPS() : Module(ModuleCategory::VISUAL, "FPS") {
    }

    void tickRenderContext(MinecraftUIRenderContext* ctx) override {
        if (enabled) {
            Vector2 winSize = ctx->ClientInstance->GetGuiData()->getScaledWindowDimensions();
            int fps = static_cast<int>(std::round(ImGui::GetIO().Framerate));

            TextHolder text(std::to_string(fps) + " FPS");

            DrawMinecraftText(Vector4(Vector2(winSize.x / 2, 0), Vector2(20, 20)), text, ColorUtils::getRainbow(5, 1, 1), 1, 1);
        }
    }

    void renderImGui() override {
        if (ImGui::CollapsingHeader("FPS", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Displays FPS.");
            ImGui::Spacing();
            ImGui::Toggle("Enable FPS", &this->enabled);
        }
    }
};