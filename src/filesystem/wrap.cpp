#include "filesystem/wrap.h"
#include "filesystem/filesystem.h"

static int w_exists(lua_State *L) {
	std::string path = luax_checkstring(L, 1);
	auto result = limb::filesystem::FileExists(path);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}
	
	lua_pushboolean(L, (*result ? 1 : 0));
	return 1;
}

static int w_isPathRelative(lua_State *L) {
	std::string path = luax_checkstring(L, 1);
	auto result = limb::filesystem::IsPathRelative(path);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}

	lua_pushboolean(L, (*result ? 1 : 0));
	return 1;
}

static int w_isPathAbsolute(lua_State *L) {
	std::string path = luax_checkstring(L, 1);
	auto result = limb::filesystem::IsPathAbsolute(path);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}

	lua_pushboolean(L, (*result ? 1 : 0));
	return 1;
}

static int w_normalizePath(lua_State *L) {
	std::string str_path = luax_checkstring(L, 1);
	auto result = limb::filesystem::NormalizePath(str_path);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}

	lua_pushstring(L, result.value().c_str());
	return 1;
}

static int w_removeExtension(lua_State *L) {
	std::string str_path = luax_checkstring(L, 1);
	auto result = limb::filesystem::RemoveExtension(str_path);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}

	lua_pushstring(L, result.value().c_str());
	return 1;
}

static int w_getCurrentPath(lua_State *L) {
	std::string path = limb::filesystem::GetCurrentPath();
	lua_pushstring(L, path.c_str());
	return 1;
}

static const luaL_Reg functions[] = {
	{ "exists", w_exists },
	{ "isPathRelative", w_isPathRelative },
	{ "isPathAbsolute", w_isPathAbsolute },
	{ "normalizePath", w_normalizePath },
	{ "removeExtension", w_removeExtension },
	{ "getCurrentPath", w_getCurrentPath },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_filesystem(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}