#include "graphics/graphics.h"

namespace limb {
namespace graphics {

void Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SetBackgroundColor(const Color& color) {
	bgColor = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void Present() {
	limb::window->SwapBuffers();
}

} // namespace graphics
} // namespace limb
