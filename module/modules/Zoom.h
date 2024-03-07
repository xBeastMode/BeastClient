class Zoom : public Module {
public:
    Zoom() : Module(ModuleCategory::VISUAL, "Zoom") {
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
        if (ImGui::CollapsingHeader("Zoom", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Allows you to zoom in and out\nlike optifine with C key.");
            ImGui::Spacing();
            ImGui::Toggle("Enable Zoom", &this->enabled);
        }
    }
};