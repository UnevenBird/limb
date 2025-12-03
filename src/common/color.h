#ifndef LIMB_COLOR_H
#define LIMB_COLOR_H

namespace limb {

struct Color {
	float r, g, b, a;
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
	Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
};

} // namespace limb

#endif // LIMB_COLOR_H
