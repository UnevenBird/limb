#include "common/color.h"

namespace limb {

void HSVtoRGB(const Color& in, Color& out) {
	float h = std::fmod(in.r, 360.0f);
	if (h < 0) h += 360.f;

	float s = clamp01(in.g);
	float v = clamp01(in.b);
	float a = clamp01(in.a);

	if (s <= 0) {
		out = {v, v, v, a};
		return;
	}
	if (v <= 0) {
		out = {0, 0, 0, a};
		return;
	}

	float C = v * s;
	float hp = h / 60.0f;
	float X = C * (1 - std::fabs(std::fmod(hp, 2.0f) - 1));
	float m = v - C;

	float r1, g1, b1;
	switch (int(std::floor(hp)) % 6) {
		case 0: r1 = C; g1 = X; b1 = 0; break;
		case 1: r1 = X; g1 = C; b1 = 0; break;
		case 2: r1 = 0; g1 = C; b1 = X; break;
		case 3: r1 = 0; g1 = X; b1 = C; break;
		case 4: r1 = X; g1 = 0; b1 = C; break;
		default: r1 = C; g1 = 0; b1 = X; break;
	}

	out.r = r1 + m;
	out.g = g1 + m;
	out.b = b1 + m;
	out.a = a;
}

} // namespace limb
