#pragma once

static bool drawImGui = true;
static bool firstDraw = true;

void RenderGUI() {
    ImGui::NewFrame();
    {
        if (drawImGui && guiData != nullptr) {
            ImGuiStyle& style = ImGui::GetStyle();

            style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.98f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.18f, 0.18f, 0.18f, 0.00f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.08f, 0.08f, 0.08f, 0.50f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.60f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 0.90f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.83f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.71f, 0.71f, 1.00f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.60f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.29f, 0.29f, 0.29f, 0.90f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.60f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.29f, 0.29f, 0.29f, 0.90f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.60f, 0.78f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.60f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.29f, 0.29f, 0.29f, 0.90f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 0.86f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.60f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.12f, 0.12f, 0.97f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

            ImGuiWindowFlags TargetFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

            ImGuiIO& io = ImGui::GetIO();

            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

            if (ImGui::Begin(("Beast Client 1.0"), 0, TargetFlags)) {
                ImGui::Text("Beast Client 1.0");

                if (ImGui::CollapsingHeader("Visuals", ImGuiTreeNodeFlags_DefaultOpen)) {
                    for (Module* module : module_manager.getModulesInCategory(ModuleCategory::VISUAL)) {
                        module->renderImGui();
                    }
                }

                dbg_console.Draw();
                ImGui::End();
            }

            for (Module* module : module_manager.getModulesInCategory(ModuleCategory::VISUAL)) {
                module->renderAutonomousImGui();
            }
        }
    }

    ImGui::Render();
}

void RenderMinecraftUI(MinecraftUIRenderContext* ctx) {
    if (guiData == nullptr) return;
    if (oFont == nullptr) return;

    for (Module* mod : module_manager.getAllModules()) {
        mod->tickRenderContext(ctx);
    }

    Vector2 windowSize = guiData->getScaledWindowDimensions();
    int index = 0;

    for (Module* mod : module_manager.getAllModules()) {
        if (mod->enabled or mod->name == "Watermark") {
            TextHolder text = TextHolder(mod->name);
            if (mod->name == "Watermark") {
                text = TextHolder(mod->description);
            }

            float pos1 = -0 + windowSize.x - ctx->getLineLength(*oFont, text, 1, false);
            float pos2 = 0 + (index * (16.f / 1.6));

            DrawMinecraftText(Vector4(Vector2(pos1 - 2, pos2), Vector2(20, 20)), text, ColorUtils::getRainbow(3, 1, 1, index * (100)), 1, 1);
            ++index;
        }
    }
}