#ifndef LIMB_COLOR_H
#define LIMB_COLOR_H

#include <cmath>

static float clamp01(float x) noexcept {
	if (x <= 0.0f) return 0.0f;
	if (x >= 1.0f) return 1.0f;
	return x;
}

namespace limb {

struct Color {
	float r, g, b, a;
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
	Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
};

void HSVtoRGB(const Color& in, Color& out);

} // namespace limb

#endif // LIMB_COLOR_H
