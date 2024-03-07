#pragma once

class KeyDisplay : public Module {
public:
    KeyDisplay() : Module(ModuleCategory::VISUAL, "Key Display") {
    }

    void tickRenderContext(MinecraftUIRenderContext* ctx) override {
        ClientInstance* ci = ctx->ClientInstance;

        Vector2 winSize = ci->GetGuiData()->getScaledWindowDimensions();
        Vector2 currSize = winSize;

        if (enabled) {
            currSize.x = 5;
            currSize.y -= 20;

            int key = keyNameToKey["SPACE"];
            auto held = keyMap.find(key);

            UIColor space(55, 55, 55, 255);

            if (held != keyMap.end()) {
                if (held->second == true) {
                    space = UIColor(0, 0, 0, 255);
                }
            }

            ctx->fillRectangle(Vector4(currSize, Vector2(47, 15)), space, 0.5);

            int buttonWidth = 15;
            int buttonHeight = 15;
            int margin = 1;
            int borderWidth = 1;

            Vector2 dim = winSize;

            const char* buttonText[] = { "A", "S", "D", "LMB", "W", "RMB" };
            int numButtons = sizeof(buttonText) / sizeof(buttonText[0]);

            UIColor color = ColorUtils::getRainbow(5, 1, 1);

            int maxButtonsPerRow = 3;
            int numRows = (numButtons + maxButtonsPerRow - 1) / maxButtonsPerRow;

            int index = 0;

            for (int i = 0; i < numButtons; i++) {
                color = ColorUtils::getRainbow(5, 1, 1);

                int row = i / maxButtonsPerRow;
                int col = i % maxButtonsPerRow;

                const char* btntxt = buttonText[i];

                int x = col * (buttonWidth + margin);
                int y = dim.y - ((row + 1) * (buttonHeight + margin));

                Vector4 pos(Vector2(x + 5, y - 20), Vector2(buttonWidth, buttonHeight));
                Vector4 pos2(pos.w - borderWidth, pos.x + borderWidth, pos.y - borderWidth, pos.z + borderWidth);

                UIColor btncolor(55, 55, 55, 255);

                key = keyNameToKey[btntxt];
                held = keyMap.find(key);

                if (held != keyMap.end()) {
                    if (held->second == true) {
                        btncolor = UIColor(0, 0, 0, 255);
                    }
                }

                ctx->fillRectangle(pos, btncolor, 0.5);
                //ctx->drawRectangle(pos2, ColorUtils::getRainbow(5, 1, 1, index * (100)), 0.5, borderWidth);

                pos.w += 3;
                pos.y += 6.5;

                TextHolder text(btntxt);
                DrawMinecraftText(pos, text, color, 0.6, 1);
                ++index;
            }
        }
    }

	void renderImGui() override {
        if (ImGui::CollapsingHeader("Key Display", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::Text("Displays keyboard/mouse input.");
            ImGui::Spacing();
            ImGui::Toggle("Enable Key Display", &this->enabled);
        }
	}
};