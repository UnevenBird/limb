#include "limb/limb.h"
#include "graphics/graphics.h"
#include "glad/glad.h"

#include <cmath>

static float clamp01(float x) noexcept {
	if (x <= 0.0f) return 0.0f;
	if (x >= 1.0f) return 1.0f;
	return x;
}

namespace limb {
namespace graphics {

void Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SetBackgroundColor(const Color& color) {
	bg_color = color;
	glClearColor(bg_color.r, bg_color.g, bg_color.b, bg_color.a);
}

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

void Present() {
	if (!limb::app::HasWindow()) return;
	limb::app::window->SwapBuffers();
}

void SetWireframe(bool state) {
	if (state) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void BindShader(const Shader* shader) {
	glUseProgram(shader->GetProgram());
}

void UnbindShader() {
	glUseProgram(0);
}

void Render(const Mesh* mesh) {
	GLuint vao = mesh->GetVAO();
	GLuint ebo = mesh->GetEBO();
	if (vao == 0 || ebo == 0) return;

	GLsizei index_count = mesh->GetIndexCount();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	// glBindVertexArray(0); // no need to unbind it every time
}

} // namespace graphics
} // namespace limb
