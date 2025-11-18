#include "window/window.h"

namespace limb {

Window::Window(std::string &title, int width, int height)
	: m_hints(nullptr)
	, m_title(title)
	, m_width(width)
	, m_height(height)
	, m_flags(RGFW_windowOpenGL | RGFW_windowCenter)
{}

Window::~Window() {
	if (!m_window) return;
	RGFW_window_close(m_window);
	m_window = nullptr;
}

bool Window::Init() {
	m_hints = RGFW_getGlobalHints_OpenGL();
	m_hints->profile = RGFW_glCore;
	m_hints->major = 3;
	m_hints->minor = 3;
	m_hints->debug = RGFW_FALSE;
	m_hints->sRGB = RGFW_FALSE;
	RGFW_setGlobalHints_OpenGL(m_hints);

	m_window = RGFW_createWindow(m_title.c_str(), 0, 0, m_width, m_height, m_flags);
	if (!m_window) {
		return false;
	}
	RGFW_window_makeCurrentContext_OpenGL(m_window);

	if (!gladLoadGLLoader((GLADloadproc)RGFW_getProcAddress_OpenGL)) {
		RGFW_window_close(m_window);
		m_window = nullptr;
		return false;
	}

	if (RGFW_window_isHidden(m_window)) RGFW_window_show(m_window);

	return true;
}

void Window::SwapBuffers() {
	RGFW_window_swapBuffers_OpenGL(m_window);
}

RGFW_window*  Window::GetHandler() {
	return m_window;
}

} // namespace limb
