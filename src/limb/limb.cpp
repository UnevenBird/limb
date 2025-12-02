#include "limb/limb.h"
#include "fmt/format.h"
#include "filesystem/filesystem.h"

namespace limb {
namespace app {

bool Initialize() {
	auto fs_result = filesystem::Init();
	if (!fs_result) {
		fmt::println("PhysFS error: {}", fs_result.error());
		return false;
	}

	timer = new Timer();
	timer->Init();
	return true;
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