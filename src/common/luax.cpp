#include "luax.h"

int luax_premakeglobal(lua_State* L, const char *k) {
	lua_getglobal(L, k);
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setglobal(L, k);
	}
	return 1;
}

int luax_preloadlib(lua_State* L, lua_CFunction f, const char *name) {
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, f);
	lua_setfield(L, -2, name);
	lua_pop(L, 2);
	return 0;
}

void luax_setfuncs(lua_State* L, const luaL_Reg *l) {
	if (l == nullptr)
		return;

	for (; l->name != nullptr; l++)
	{
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
