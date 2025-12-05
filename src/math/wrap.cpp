#include "math/mathlib.h"
#include "math/wrap.h"

static int w_clamp(lua_State* L) {
	if (lua_isnumber(L, 1)) {
		double val = luaL_checknumber(L, 1);
		double low = luaL_checknumber(L, 2);
		double high = luaL_checknumber(L, 3);
		lua_pushnumber(L, limb::math::clamp(val, low, high));
		return 1;
	} else {
		return luax_typerror(L, 1, "number");
	}
}

static const luaL_Reg functions[] = {
	{ "clamp", w_clamp },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_math(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}