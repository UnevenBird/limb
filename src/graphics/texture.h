#ifndef LIMB_TEXTURE_H
#define LIMB_TEXTURE_H

#include "filesystem/filesystem.h"
#include <tl/expected.hpp>

namespace limb {
namespace graphics {

class Texture {
public:
	Texture() = default;
	~Texture();

	tl::expected<bool, std::string> Init(const std::string& str_path);
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	int GetChannels() const { return m_channels; }
	const unsigned char* GetData() const { return m_image_data; }

private:
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
	unsigned char* m_image_data = nullptr;
};

} // namespace graphics
} // namespace limb

#endif // LIMB_TEXTURE_H
