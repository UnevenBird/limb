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

extern "C" void luax_register_type(lua_State* L, const char* name, const luaL_Reg* functions);
int luax_premakeglobal(lua_State* L, const char* k);
int luax_preloadlib(lua_State* L, lua_CFunction f, const char* name);
void luax_setfuncs(lua_State* L, const luaL_Reg* l);
int luax_resume(lua_State* L, int nargs, int* nres);
std::string luax_checkstring(lua_State* L, int idx);
float luax_tofloat(lua_State* L, int idx);
float luax_checkfloat(lua_State* L, int idx);
float luax_optfloat(lua_State* L, int idx, lua_Number def);
bool luax_checkcolor(lua_State* L, int index, limb::Color& color);
int luax_typerror(lua_State* L, int idx, const char* expected);
int luax_tabletyperror(lua_State* L, int idx, int tblidx, const char* expected);
int luax_argcerror(lua_State* L, int min);
int luax_argcerror(lua_State* L, int min, int max);

template<typename T>
T* luax_checkuserdata(lua_State* L, int idx, const char* name) {
	void* ud = luaL_checkudata(L, idx, name);
	if (!ud) luaL_error(L, "%s expected", name);
	return static_cast<T*>(ud);
}

bool luax_isuserdata(lua_State* L, int idx, const char* name);

#endif // LIMB_LUAX_H
