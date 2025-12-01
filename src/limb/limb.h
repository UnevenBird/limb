#ifndef LIMB_H
#define LIMB_H

#include <tl/expected.hpp>

#include "timer/timer.h"
#include "window/window.h"

namespace limb {
namespace app {

inline Window* window = nullptr;
inline Timer* timer = nullptr;

void Initialize(int argc, char **argv);
bool HasWindow();
tl::expected<bool, std::string> InitWindow(const std::string &title, int width, int height);
void Shutdown();

} // namespace app
} // namespace limb

#endif // LIMB_H
