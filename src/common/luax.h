#ifndef LIMB_LUAX_H
#define LIMB_LUAX_H

#include <string>
#include "common/config.h"
#include "common/color.h"

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

int luax_premakeglobal(lua_State* L, const char* k);
int luax_preloadlib(lua_State* L, lua_CFunction f, const char* name);
void luax_setfuncs(lua_State* L, const luaL_Reg* l);
int luax_resume(lua_State* L, int nargs, int* nres);
std::string luax_checkstring(lua_State* L, int idx);
bool luax_checkcolor(lua_State* L, int index, limb::Color& color);

template<typename T>
T* luax_checkuserdata(lua_State* L, int idx, const char* name) {
	void* ud = luaL_checkudata(L, idx, name);
	if (!ud) luaL_error(L, "%s expected", name);
	return static_cast<T*>(ud);
}

#endif // LIMB_LUAX_H
