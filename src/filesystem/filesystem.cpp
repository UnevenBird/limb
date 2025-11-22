#include "filesystem/filesystem.h"
#include "common/config.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace limb {
namespace filesystem {

tl::expected<bool, std::string> FileExists(const std::string& str_path) {
	if (str_path.empty()) return tl::unexpected<std::string>("invalid path provided.");

	fs::path path(str_path);
	std::error_code ec;

	if (path.is_relative()) {
		path = fs::current_path(ec) / path;
		if (ec) return tl::unexpected<std::string>(ec.message());
	}

	path = path.lexically_normal();

	if (!fs::exists(path)) return false;

	bool is_file = fs::is_regular_file(path, ec);
	if (ec) return tl::unexpected<std::string>("filesystem error: " + ec.message());
	
	bool is_symlink = fs::is_symlink(path, ec);
	if (ec) return tl::unexpected<std::string>("filesystem error: " + ec.message());

	return (is_file && !is_symlink);
}

tl::expected<bool, std::string> IsPathRelative(const std::string& str_path) {
	if (str_path.empty()) return tl::unexpected<std::string>("invalid path provided.");
	fs::path path(str_path);
	return path.is_relative();
}

tl::expected<bool, std::string> IsPathAbsolute(const std::string& str_path) {
	if (str_path.empty()) return tl::unexpected<std::string>("invalid path provided.");
	fs::path path(str_path);
	return path.is_absolute();
}

tl::expected<std::string, std::string> NormalizePath(const std::string& str_path) {
	if (str_path.empty()) return tl::unexpected<std::string>("invalid path provided.");
	fs::path path(str_path);
	return path.lexically_normal().string();
}

std::string GetCurrentPath() {
	return fs::current_path().string();
}

} // namespace filesystem
} // namespace limb
