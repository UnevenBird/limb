#include "glm/vec2.hpp"
#include "math/wrap_vec2.h"

extern "C" int w_newVec2(lua_State *L) {
	float x = luax_optfloat(L, 1, 0.0f);
	float y = luax_optfloat(L, 2, x);

	void* ud = lua_newuserdata(L, sizeof(glm::vec2));
	glm::vec2* vec = new(ud) glm::vec2(x, y);
	
	luaL_getmetatable(L, "Vec2");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_set(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec2>(L, 1, "Vec2");
	if (lua_istable(L, 2)) {
		if (lua_objlen(L, 2) < 2) return luax_argcerror(L, 2);
		
		for (int i=1; i <= 2; i++) {
			lua_rawgeti(L, 2, i);
		}
		
		vec->x = luax_checkfloat(L, -2);
		vec->y = luax_checkfloat(L, -1);
		lua_pop(L, 2);
		return 0;

	} else if (lua_gettop(L)-1) {
		vec->x = luax_checkfloat(L, 2);
		vec->y = luax_checkfloat(L, 3);
		return 0;

	} else {
		return luax_typerror(L, 1, "table or 2 numbers");
	}
}

static int w_get(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec2>(L, 1, "Vec2");
	lua_pushnumber(L, vec->x);
	lua_pushnumber(L, vec->y);
	return 2;
}

static int w_gc(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec2>(L, 1, "Vec2");
	using type = glm::vec2;
	vec->~type();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec2>(L, 1, "Vec2");
	lua_pushfstring(L, "Vec2 (%p)", vec);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "set", w_set },
	{ "get", w_get },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void register_Vec2(lua_State* L) {
	luaL_newmetatable(L, "Vec2");
	luax_setfuncs(L, functions);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}