#ifndef LIMB_LUAX_H
#define LIMB_LUAX_H

#include "common/config.h"

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

int luax_premakeglobal(lua_State* L, const char *k);
int luax_preloadlib(lua_State* L, lua_CFunction f, const char *name);
void luax_setfuncs(lua_State* L, const luaL_Reg *l);
int luax_resume(lua_State* L, int nargs, int* nres);

#endif // LIMB_LUAX_H
