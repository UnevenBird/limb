#ifndef LIMB_TEXTURE_H
#define LIMB_TEXTURE_H

#include "glad/glad.h"
#include "common/color.h"

namespace limb {
namespace graphics {

class Texture {
public:
	Texture();
	~Texture();

	int width = 0;
	int height = 0;
private:
};

} // namespace graphics
} // namespace limb

#endif // LIMB_TEXTURE_H
