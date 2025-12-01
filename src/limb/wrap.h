#ifndef LIMB_WRAP_H
#define LIMB_WRAP_H

#include "common/luax.h"

extern "C" {
int luaopen_limb(lua_State *L);
int luaopen_limb_boot(lua_State *L);
extern int luaopen_limb_window(lua_State *L);
extern int luaopen_limb_timer(lua_State *L);
extern int luaopen_limb_event(lua_State *L);
extern int luaopen_limb_graphics(lua_State *L);
extern int luaopen_limb_filesystem(lua_State *L);
}

#endif // LIMB_WRAP_H
