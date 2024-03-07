#pragma once

class ColorUtils {
public:
	static inline float ImFmod(float x, float y) { return fmodf(x, y); }
	static inline void hsvToRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
		if (s == 0.0f) {
			out_r = out_g = out_b = v;
			return;
		}
		h = ImFmod(h, 1.0f) / (60.0f / 360.0f);
		int i = (int)h;
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));
		switch (i) {
		case 0:
			out_r = v;
			out_g = t;
			out_b = p;
			break;
		case 1:
			out_r = q;
			out_g = v;
			out_b = p;
			break;
		case 2:
			out_r = p;
			out_g = v;
			out_b = t;
			break;
		case 3:
			out_r = p;
			out_g = q;
			out_b = v;
			break;
		case 4:
			out_r = t;
			out_g = p;
			out_b = v;
			break;
		case 5:
		default:
			out_r = v;
			out_g = p;
			out_b = q;
			break;
		}
	}

	static UIColor rgbToHSV(UIColor rgb) // HSV
	{
		UIColor out = UIColor(0, 0, 0);
		double min, max, delta;

		min = rgb.r < rgb.g ? rgb.r : rgb.g;
		min = min < rgb.b ? min : rgb.b;

		max = rgb.r > rgb.g ? rgb.r : rgb.g;
		max = max > rgb.b ? max : rgb.b;

		out.b = max;
		delta = max - min;
		if (delta < 0.00001)
		{
			out.g = 0;
			out.r = 0;
			return out;
		}
		if (max > 0.0) {
			out.g = (delta / max);
		}
		else {
			out.g = 0.0;
			out.r = NAN;
			return out;
		}
		if (rgb.r >= max)
			out.r = (rgb.g - rgb.b) / delta;
		else
			if (rgb.g >= max)
				out.r = 2.0 + (rgb.b - rgb.r) / delta;
			else
				out.r = 4.0 + (rgb.r - rgb.g) / delta;

		out.r *= 60.0;

		if (out.r < 0.0)
			out.r += 360.0;

		return out;
	}

	// Returns the current millisecond ( from stack overflow )
	static __int64 getCurrentMs() {
		FILETIME f;
		GetSystemTimeAsFileTime(&f);
		(long long)f.dwHighDateTime;
		__int64 nano = ((__int64)f.dwHighDateTime << 32LL) + (__int64)f.dwLowDateTime;
		return (nano - 116444736000000000LL) / 10000;
	}

	static UIColor getRainbow(float speedInSeconds, float s, float v)
	{
		float hue = ((getCurrentMs()) % (int)(((int)speedInSeconds) * 700)) / (float)(((int)speedInSeconds) * 700);
		float r, g, b = 0;
		hsvToRGB(hue, s, v, r, g, b);
		return UIColor(r*255, g*255, b*255, 255);
	}

	static UIColor getRainbow(float speedInSeconds, float s, float v, long index)
	{
		float hue = ((getCurrentMs() + index) % (int)(((int)speedInSeconds) * 1000)) / (float)(((int)speedInSeconds) * 1000);
		float r, g, b = 0;
		hsvToRGB(hue, s, v, r, g, b);
		return UIColor(r * 255, g * 255, b * 255, 255);
	}
};