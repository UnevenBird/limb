#ifndef LIMB_GRAPHICS_H
#define LIMB_GRAPHICS_H

#include "common/color.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"

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
void Render(const Mesh* mesh);

} // namespace graphics
} // namespace limb

#endif // LIMB_GRAPHICS_H
