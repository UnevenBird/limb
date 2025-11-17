#include "timer/wrap.h"
#include "timer/timer.h"

static int w_create(lua_State *L) {
	limb::timer = new limb::Timer();
	limb::timer->Init();
	return 0;
}

static int w_step(lua_State* L) {
	double delta = limb::timer->Step();
	lua_pushnumber(L, delta);
	return 1;
}

static int w_getDelta(lua_State* L) {
	lua_pushnumber(L, (lua_Number) limb::timer->GetDelta());
	return 1;
}

static int w_getFPS(lua_State* L) {
	lua_pushnumber(L, (lua_Integer) limb::timer->GetFPS());
	return 1;
}

static int w_getTime(lua_State* L) {
	lua_pushnumber(L, (lua_Number) limb::timer->GetTime());
	return 1;
}

static const luaL_Reg functions[] = {
	{ "create", w_create },
	{ "step", w_step },
	// { "sleep", w_sleep },
	{ "getDelta", w_getDelta },
	{ "getFPS", w_getFPS },
	{ "getTime", w_getTime },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_timer(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}