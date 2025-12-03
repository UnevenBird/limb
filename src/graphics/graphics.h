#ifndef LIMB_GRAPHICS_H
#define LIMB_GRAPHICS_H

#include "common/color.h"
#include "graphics/shader.h"

namespace limb {
namespace graphics {

inline Color bg_color;

void Clear();
void SetBackgroundColor(const Color& color);
void HSVtoRGB(const Color& in, Color& out);
void Present();
void SetWireframe(bool state);
void BindShader(const Shader* shader);
void UnbindShader();

} // namespace graphics
} // namespace limb

#endif // LIMB_GRAPHICS_H
