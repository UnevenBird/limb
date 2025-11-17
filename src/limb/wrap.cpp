#include "limb/wrap.h"
#include "common/config.h"

static const char boot_lua[] =
#include "scripts/boot.lua"
;

static const luaL_Reg modules[] = {
	{ "limb.boot", luaopen_limb_boot },
	{ "limb.window", luaopen_limb_window },
	{ "limb.timer", luaopen_limb_timer },
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

static const luaL_Reg functions[] = {
	{ "getOS", w_getOS },
	{ "getVersion", w_getVersion },
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

namespace limb {

APP_STATE runlimb(APP_STATE &retval) {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luax_preloadlib(L, luaopen_limb, "limb");

	lua_getglobal(L, "require");
	lua_pushstring(L, "limb");
	lua_call(L, 1, 1);

	lua_pop(L, 1);

	lua_getglobal(L, "require");
	lua_pushstring(L, "limb.boot");
	lua_call(L, 1, 1);

	lua_newthread(L);
	lua_pushvalue(L, -2);
	int stackpos = lua_gettop(L);
	int nres = 0;
	while (luax_resume(L, 0, &nres) == LUA_YIELD) {
#if LUA_VERSION_NUM >= 504
		lua_pop(L, nres);
#else
		lua_pop(L, lua_gettop(L) - stackpos);
#endif
	}

	retval = APP_STATE::QUIT;
	if (!lua_isnoneornil(L, stackpos) && lua_isnumber(L, stackpos)) {
		retval = (APP_STATE)lua_tonumber(L, stackpos);
	}

	lua_close(L);
	return retval;
}

} // namespace limb
