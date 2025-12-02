#include "limb/limb.h"
#include "graphics/graphics.h"
#include "glad/glad.h"

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
	if (!limb::app::HasWindow()) return;
	limb::app::window->SwapBuffers();
}

} // namespace graphics
} // namespace limb
