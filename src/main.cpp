#include "limb/limb.h"
#include "limb/wrap.h"

enum class APP_STATE {
	RUN = 0,
	QUIT = 1,
};

static APP_STATE limb_run(APP_STATE &retval) {
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

int main(int argc, char **argv) {
    limb::app::Initialize(argc, argv);

	APP_STATE retval = APP_STATE::QUIT;
	do {
		retval = limb_run(retval);
	} while (retval != APP_STATE::QUIT);

	limb::app::Shutdown();
	return 0;
}
