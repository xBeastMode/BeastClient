#pragma once

class DebugConsole
{
public:
    void Clear()
    {
        buffer.clear();
    }

    void Print(const char* text)
    {
        buffer.append(text);
        buffer.push_back('\n');
    }

    void Draw()
    {
        if (ImGui::CollapsingHeader("Debug Console", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            ImGui::TextUnformatted(buffer.c_str());
        }
    }

private:
    std::string buffer;
};

static DebugConsole dbg_console;