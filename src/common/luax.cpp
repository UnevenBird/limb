#include "luax.h"

int luax_premakeglobal(lua_State* L, const char* k) {
	lua_getglobal(L, k);
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setglobal(L, k);
	}
	return 1;
}

int luax_preloadlib(lua_State* L, lua_CFunction f, const char* name) {
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, f);
	lua_setfield(L, -2, name);
	lua_pop(L, 2);
	return 0;
}

void luax_setfuncs(lua_State* L, const luaL_Reg* l) {
	if (l == nullptr)
		return;

	for (; l->name != nullptr; l++) {
		lua_pushcfunction(L, l->func);
		lua_setfield(L, -2, l->name);
	}
}

int luax_resume(lua_State* L, int nargs, int* nres) {
#if LUA_VERSION_NUM >= 504
	return lua_resume(L, nullptr, nargs, nres);
#else
	LIMB_UNUSED(nres);
	return lua_resume(L, nargs);
#endif
}

std::string luax_checkstring(lua_State* L, int idx) {
	size_t len;
	const char *str = luaL_checklstring(L, idx, &len);
	return std::string(str, len);
}

float luax_tofloat(lua_State* L, int idx) {
	return static_cast<float>(lua_tonumber(L, idx));
}

float luax_checkfloat(lua_State* L, int idx) {
	return static_cast<float>(luaL_checknumber(L, idx));
}

float luax_optfloat(lua_State* L, int idx, lua_Number def) {
	return static_cast<float>(luaL_optnumber(L, idx, def));
}

bool luax_checkcolor(lua_State* L, int index, limb::Color& color) {
	int top = lua_gettop(L);
	if (index < 1 || index > top) {
		return false;
	}

	if (lua_istable(L, index)) {
		for (int i = 1; i <= 4; i++) {
			lua_rawgeti(L, index, i);
		}
		color.r = luax_checkfloat(L, -4);
		color.g = luax_checkfloat(L, -3);
		color.b = luax_checkfloat(L, -2);
		color.a = luax_optfloat(L, -1, 1.0f);
		lua_pop(L, 4);
		return true;
	} else if (lua_gettop(L) >= index + 2) {
		color.r = luax_checkfloat(L, index);
		color.g = luax_checkfloat(L, index + 1);
		color.b = luax_checkfloat(L, index + 2);
		color.a = luax_optfloat(L, index + 3, 1.0f);
		return true;
	} else if (lua_gettop(L) <= index + 1) {
		uint32_t x = (uint32_t) luaL_checkinteger(L, index);
		color.r = ((x >> 16) & 0xff) / 255.0f;
		color.g = ((x >> 8) & 0xff) / 255.0f;
		color.b = ((x >> 0) & 0xff) / 255.0f;
		color.a = luax_optfloat(L, index + 1, 1.0f);
		return true;
	}

	return false;
}

int luax_typerror(lua_State* L, int idx, const char* expected) {
	int type = lua_type(L, idx);
	const char* tname = lua_typename(L, type);
	const char* msg = lua_pushfstring(L, "%s expected, got %s", expected, tname);
	return luaL_argerror(L, idx, msg);
}

int luax_tabletyperror(lua_State* L, int idx, int tblidx, const char* expected) {
	lua_rawgeti(L, idx, tblidx);
	int type = lua_type(L, -1);
	const char* tname = lua_typename(L, type);
	const char* msg = lua_pushfstring(L, "%s expected at index #%d, got %s", expected, tblidx, tname);
	lua_pop(L, 2);
	return luaL_argerror(L, idx, msg);
}