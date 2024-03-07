#pragma once

HWND mainWindow;
HMODULE mainModule;

static uintptr_t optr;
static MinecraftUIRenderContext* oContext;
static GuiData* guiData;
static ClientInstance* clientInstance;
static Actor* localPlayer;
static Font* oFont;

std::vector<std::string> logo = splitStringToVector("BeastClient");

static long _moves;
static long moves;

static std::map<const char*, int> keyNameToKey = {
    {"LMB", 1},
    {"W", 87},
    {"RMB", 2},
    {"A", 65},
    {"S", 83},
    {"D", 68},
    {"SPACE", 32}
};

static std::vector<int> acceptedKeys = { 1, 2, 65, 87, 68, 83, 32 };
static std::map<__int16, bool> keyMap;

void DrawMinecraftText(const Vector4& pos, TextHolder& text, const UIColor& color, float textSize, float alpha) {
    if (oContext == nullptr) return;
    if (oFont == nullptr) return;

    static CaretMeasureData caretMeasureData = CaretMeasureData();

    TextMeasureData textMeasure{};
    textMeasure.textSize = textSize;

    oContext->drawText(*oFont, pos, text, color, alpha, 0, textMeasure, caretMeasureData);
    oContext->flushText(0);
}

static bool running = true;