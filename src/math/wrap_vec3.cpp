#include "glm/vec3.hpp"
#include "math/wrap_vec3.h"

extern "C" int w_newVec3(lua_State *L) {
	float x = luax_optfloat(L, 1, 0.0f);
	float y = luax_optfloat(L, 2, x);
	float z = luax_optfloat(L, 3, x);

	void* ud = lua_newuserdata(L, sizeof(glm::vec3));
	glm::vec3* vec = new(ud) glm::vec3(x, y, z);
	
	luaL_getmetatable(L, "Vec3");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_set(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec3>(L, 1, "Vec3");
	if (lua_istable(L, 2)) {
		if (lua_objlen(L, 2) < 3) return luax_argcerror(L, 3);
		
		for (int i=1; i <= 3; i++) {
			lua_rawgeti(L, 2, i);
		}
		
		vec->x = luax_checkfloat(L, -3);
		vec->y = luax_checkfloat(L, -2);
		vec->z = luax_checkfloat(L, -1);
		lua_pop(L, 3);
		return 0;

	} else if (lua_gettop(L)-1) {
		vec->x = luax_checkfloat(L, 2);
		vec->y = luax_checkfloat(L, 3);
		vec->z = luax_checkfloat(L, 4);
		return 0;

	} else {
		return luax_typerror(L, 2, "table or 3 numbers");
	}
}

static int w_get(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec3>(L, 1, "Vec3");
	lua_pushnumber(L, vec->x);
	lua_pushnumber(L, vec->y);
	lua_pushnumber(L, vec->z);
	return 3;
}

static int w_gc(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec3>(L, 1, "Vec3");
	using type = glm::vec3;
	vec->~type();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* vec = luax_checkuserdata<glm::vec3>(L, 1, "Vec3");
	lua_pushfstring(L, "Vec3 (%p)", vec);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "set", w_set },
	{ "get", w_get },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void register_Vec3(lua_State* L) {
	luaL_newmetatable(L, "Vec3");
	luax_setfuncs(L, functions);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}