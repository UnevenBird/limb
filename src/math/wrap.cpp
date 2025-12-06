#include "math/mathlib.h"
#include "math/wrap.h"

#include "math/wrap_vec2.h"
#include "math/wrap_vec3.h"
#include "math/wrap_vec4.h"

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
	{ "newVec2", w_newVec2 },
	{ "newVec3", w_newVec3 },
	{ "newVec4", w_newVec4 },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_math(lua_State *L) {
	luaopen_limb_Vec2(L);
	luaopen_limb_Vec3(L);
	luaopen_limb_Vec4(L);

	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}