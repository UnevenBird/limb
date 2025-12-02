#ifndef LIMB_GRAPHICS_H
#define LIMB_GRAPHICS_H

#include "common/color.h"

namespace limb {
namespace graphics {

inline Color bgColor;

void Clear();
void SetBackgroundColor(const Color& color);
void Present();

} // namespace graphics
} // namespace limb

#endif // LIMB_GRAPHICS_H
