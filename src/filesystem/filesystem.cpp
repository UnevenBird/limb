#include "filesystem/filesystem.h"
#include "physfs.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace limb {
namespace filesystem {

tl::expected<bool, std::string> Init() {
	std::string cwd = fs::current_path().string();
	PHYSFS_init(cwd.c_str());
	if (!PHYSFS_isInit()) {
		return tl::unexpected<std::string>(PHYSFS_getLastError());
	}
	return true;
}

tl::expected<bool, std::string> FileExists(const std::string& str_path) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");

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

// tl::expected<bool, std::string> Mount(const std::string& str_path) {
// 	auto result = FileExists(str_path);
// 	if (!result) return result;
	
// 	bool success = PHYSFS_mount(str_path.c_str(), mountpoint, appendToPath) != 0;
// 	return true;
// }

tl::expected<bool, std::string> IsPathRelative(const std::string& str_path) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");
	return path.is_relative();
}

tl::expected<bool, std::string> IsPathAbsolute(const std::string& str_path) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");
	return path.is_absolute();
}

tl::expected<std::string, std::string> NormalizePath(const std::string& str_path) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");
	return path.lexically_normal().string();
}

tl::expected<std::string, std::string> GetFilename(const std::string& str_path, bool remove_ext) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");
	if (!path.has_filename()) return std::string("");
	if (remove_ext && path.has_extension()) path.replace_extension("");
	return path.filename().string();
}

tl::expected<std::string, std::string> GetExtension(const std::string& str_path) {
	fs::path path(str_path);
	if (path.empty()) return tl::unexpected<std::string>("empty path provided.");
	if (!path.has_extension()) return std::string("");
	return path.extension().string();
}

std::string GetCurrentPath() {
	return fs::current_path().string();
}

} // namespace filesystem
} // namespace limb
