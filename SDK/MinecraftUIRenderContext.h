#pragma once

struct TextMeasureData {
	float textSize = 1;
	int idk = 0;
	bool displayShadow = false;
	bool bool2 = false;
};

class ComponentRenderBatch;
class NinesliceInfo;
class HashedString;

class MinecraftUIRenderContext {
public:
    uintptr_t** vtable;
    ClientInstance* ClientInstance;
	uintptr_t* screenContext;

	float getLineLength(Font& font, TextHolder& str, float textSize, bool unknown) {
		return CallVFunc<1, float, Font&, TextHolder&, float, bool>(this, font, str, textSize, unknown);
	};

	__int64 drawText(Font& font, const Vector4 &pos, TextHolder& text, const UIColor& color, float alpha, unsigned int textAlignment, const TextMeasureData& textMeasureData, const CaretMeasureData& caretMeasureData) {
		return CallVFunc<5, __int64, Font&, const Vector4&, TextHolder&, const UIColor&, float, unsigned int, const TextMeasureData&, const CaretMeasureData&>(this, font, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
	};
	void flushText(float timeSinceLastFlush) {
		return CallVFunc<6, void, float>(this, timeSinceLastFlush);
	};

    void drawRectangle(const Vector4& pos, const UIColor& c, float alpha, int lineWdidth) {
        CallVFunc<12, void, const Vector4&, const UIColor&, float, int>(this, pos, c, alpha, lineWdidth);
    }

    void fillRectangle(const Vector4& pos, const UIColor& c, float alpha) {
        CallVFunc<13, void, const Vector4&, const UIColor&, float>(this, pos, c, alpha);
    }
};