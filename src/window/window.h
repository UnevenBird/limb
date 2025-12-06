#ifndef LIMB_WINDOW_H
#define LIMB_WINDOW_H
#define RGFW_IMPORT
#define RGFW_OPENGL

#include "glad/glad.h"
#include "RGFW.h"

#include <string>

namespace limb {

class Window {
public:
	Window(const std::string &title, int width, int height);
	~Window();
	bool Init();
	void SetVisible(bool visible);
	void SetTitle(const std::string &title);
	void SwapBuffers();
	bool IsVisible();
	void Resize(int width, int height);
	RGFW_window* GetHandler();

private:
	std::string m_title;
	int m_width, m_height;
	RGFW_glHints* m_hints;
	RGFW_window* m_window;
	RGFW_windowFlags m_flags;
};

} // namespace limb

#endif // LIMB_WINDOW_H
