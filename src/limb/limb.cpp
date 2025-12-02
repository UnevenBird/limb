#include "limb/limb.h"

namespace limb {
namespace app {

void InitTimer() {
	timer = new Timer();
	timer->Init();
}

void Initialize(int argc, char **argv) {
	InitTimer();
}

bool HasWindow() {
	return window != nullptr;
}

void CloseWindow() {
	if (!HasWindow()) return;
	delete window;
	window = nullptr;
}

tl::expected<bool, std::string> InitWindow(const std::string &title, int width, int height) {
	window = new Window(title, width, height);
	if (!window->Init()) {
		CloseWindow();
		return tl::unexpected<std::string>("Couldn't initialize window."); // @todo add proper error messages
	}
	return true;
}

void Shutdown() {
	CloseWindow();
	if (timer) {
		delete timer;
		timer = nullptr;
	}
}

}
}