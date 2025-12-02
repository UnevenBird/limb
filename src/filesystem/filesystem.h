#ifndef LIMB_FILESYSTEM_H
#define LIMB_FILESYSTEM_H

#include <tl/expected.hpp>
#include <string>

namespace limb {
namespace filesystem {

tl::expected<bool, std::string> Init();
tl::expected<bool, std::string> FileExists(const std::string& str_path);
// tl::expected<bool, std::string> Mount(const std::string& str_path);
tl::expected<bool, std::string> IsPathRelative(const std::string& str_path);
tl::expected<bool, std::string> IsPathAbsolute(const std::string& str_path);
tl::expected<std::string, std::string> NormalizePath(const std::string& str_path);
tl::expected<std::string, std::string> GetFilename(const std::string& str_path, bool remove_ext);
tl::expected<std::string, std::string> GetExtension(const std::string& str_path);
std::string GetCurrentPath();

} // namespace filesystem
} // namespace limb

#endif // LIMB_FILESYSTEM_H
