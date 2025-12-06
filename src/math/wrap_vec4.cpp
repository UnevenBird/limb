#include "glm/vec4.hpp"
#include "math/wrap_vec4.h"

extern "C" int w_newVec4(lua_State *L) {
	float x = luax_optfloat(L, 1, 0.0f);
	float y = luax_optfloat(L, 2, x);
	float z = luax_optfloat(L, 3, x);
	float w = luax_optfloat(L, 4, 1.0f);

	void* ud = lua_newuserdata(L, sizeof(glm::vec4));
	glm::vec4* vec = new(ud) glm::vec4(x, y, z, w);
	
	luaL_getmetatable(L, "Vec4");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_set(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec4>(L, 1, "Vec4");
	if (lua_istable(L, 2)) {
		if (lua_objlen(L, 2) < 3) return luax_argcerror(L, 3, 4);
		
		for (int i=1; i <= 4; i++) {
			lua_rawgeti(L, 2, i);
		}
		
		vec->x = luax_checkfloat(L, -4);
		vec->y = luax_checkfloat(L, -3);
		vec->z = luax_checkfloat(L, -2);
		vec->w = luax_optfloat(L, -1, 1.0f);
		lua_pop(L, 4);
		return 0;

	} else if (lua_gettop(L)-1) {
		vec->x = luax_checkfloat(L, 2);
		vec->y = luax_checkfloat(L, 3);
		vec->z = luax_checkfloat(L, 4);
		vec->w = luax_optfloat(L, 5, 1.0f);
		return 0;

	} else {
		return luax_typerror(L, 2, "table or 3-4 numbers");
	}
}

static int w_get(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec4>(L, 1, "Vec4");
	lua_pushnumber(L, vec->x);
	lua_pushnumber(L, vec->y);
	lua_pushnumber(L, vec->z);
	lua_pushnumber(L, vec->w);
	return 4;
}

static int w_gc(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec4>(L, 1, "Vec4");
	using type = glm::vec4;
	vec->~type();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec4>(L, 1, "Vec4");
	lua_pushfstring(L, "Vec4 (%p)", vec);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "set", w_set },
	{ "get", w_get },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void luaopen_limb_Vec4(lua_State* L) {
	luax_register_type(L, "Vec4", functions);
}
