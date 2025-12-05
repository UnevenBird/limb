#include "math/mathlib.h"
#include "glm/glm.hpp"
#include <cmath>

namespace limb {
namespace math {

double clamp(double val, double low, double high) {
	return fmin(fmax(val, low), high);
}

} // namespace math
} // namespace limb