#include "limb/wrap.h"
#include "common/config.h"
#include "fmt/core.h"
#include "fmt/args.h"

static const char boot_lua[] =
#include "scripts/boot.lua"
;

static const luaL_Reg modules[] = {
	{ "limb.boot", luaopen_limb_boot },
	{ "limb.window", luaopen_limb_window },
	{ "limb.timer", luaopen_limb_timer },
	{ "limb.event", luaopen_limb_event },
	{ "limb.graphics", luaopen_limb_graphics },
	{ "limb.filesystem", luaopen_limb_filesystem },
	{ "limb.math", luaopen_limb_math },
	{ nullptr, nullptr }
};

static int w_getOS(lua_State *L) {
#if defined(LIMB_WINDOWS)
	lua_pushstring(L, "Windows");
#elif
	lua_pushstring(L, "Unknown");
#endif
	return 1;
}

static int w_getVersion(lua_State *L) {
	lua_pushinteger(L, 0);
	lua_pushinteger(L, 1);
	return 2;
}

static void fill_dynamic_arg_storage(lua_State *L, int j, int argc, fmt::dynamic_format_arg_store<fmt::format_context>& store) {
	for (int idx=j; idx <= j+argc; ++idx) {
		int type = lua_type(L, idx);
		switch (type) {
		case LUA_TNUMBER: {
			store.push_back(lua_tonumber(L, idx));
			break;
		}
		case LUA_TBOOLEAN: {
			bool b = static_cast<bool>(lua_toboolean(L, idx));
			store.push_back(lua_toboolean(L, idx) != 0);
			break;
		}
		case LUA_TSTRING: {
			store.push_back(lua_tostring(L, idx));
			break;
		}
		case LUA_TNIL: {
			store.push_back("nil");
			break;
		}
		default: { // LUA_TFUNCTION, LUA_TTABLE, LUA_TTHREAD, LUA_TUSERDATA, LUA_TLIGHTUSERDATA
			const char *type_name = luaL_typename(L, idx);
			const void *ptr = lua_topointer(L, idx);
			store.push_back(fmt::format("{}: {}", type_name, fmt::ptr(ptr)));
		}
		}
	}
}

static int w_format(lua_State *L) {
	const char *pattern = luaL_checkstring(L, 1);

	int argc = lua_gettop(L);
	if (argc == 1) {
		lua_pushstring(L, pattern);
		return 1;
	}

	fmt::dynamic_format_arg_store<fmt::format_context> store;
	fill_dynamic_arg_storage(L, 2, argc-1, store);

	try {
		std::string result = fmt::vformat(pattern, store);
		lua_pushstring(L, result.c_str());
		return 1;
	} catch (const fmt::format_error& e) {
		return luaL_error(L, "format error: %s", e.what());
	}
}

static int w_log(lua_State *L) {
	int argc = lua_gettop(L);
	if (argc == 0) {
		fmt::println("");
		return 0;
	}

	std::string pattern;
	for (int i=1; i<=argc; ++i) {
		pattern += "{}\t";
	}

	fmt::dynamic_format_arg_store<fmt::format_context> store;
	fill_dynamic_arg_storage(L, 1, argc, store);

	try {
		fmt::println("{}", fmt::vformat(pattern, store));
		return 0;
	} catch (const fmt::format_error& e) {
		return luaL_error(L, "format error: %s", e.what());
	}
}

static int w_logf(lua_State *L) {
	int argc = lua_gettop(L);
	if (argc < 2) {
		return luaL_error(L, "expected at least 2 arguments: format string and one value.");
	}

	const char *pattern = luaL_checkstring(L, 1);

	fmt::dynamic_format_arg_store<fmt::format_context> store;
	fill_dynamic_arg_storage(L, 2, argc-1, store);

	try {
		fmt::println("{}", fmt::vformat(pattern, store));
		return 0;
	} catch (const fmt::format_error& e) {
		return luaL_error(L, "format error: %s", e.what());
	}
}

static const luaL_Reg functions[] = {
	{ "getOS", w_getOS },
	{ "getVersion", w_getVersion },
	{ "format", w_format },
	{ "log", w_log },
	{ "logf", w_logf },
	{ nullptr, nullptr }
};

extern "C" {

int luaopen_limb(lua_State *L) {
	for (int i = 0; modules[i].name != nullptr; i++) {
		luax_preloadlib(L, modules[i].func, modules[i].name);
	}

	luax_premakeglobal(L, "limb");
	luax_setfuncs(L, functions);
	return 1;
}

int luaopen_limb_boot(lua_State *L) {
	if (luaL_loadbuffer(L, boot_lua, sizeof(boot_lua), "=[limb \"boot.lua\"]") == 0)
		lua_call(L, 0, 1);

	return 1;
}

} // extern "C"
