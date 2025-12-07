#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics/texture.h"
#include <filesystem>

namespace limb {
namespace graphics {

Texture::~Texture() {
	if (!m_image_data) return;
	stbi_image_free(m_image_data);
	m_image_data = nullptr;
}

tl::expected<bool, std::string> Texture::Init(const std::string& str_path) {
	auto result = limb::filesystem::FileExists(str_path);
	if (!result) return tl::unexpected<std::string>("File not found: " + str_path);

	std::filesystem::path image_path(str_path);
	m_image_data = stbi_load(image_path.string().c_str(), &width, &height, &channels, 0);
	if (!m_image_data) {
		const char* reason = stbi_failure_reason();
		return tl::unexpected(std::string("Failed to load image: ") + (reason ? reason : "unknown error"));
	}
	return true;
}

} // namespace graphics
} // namespace limb
