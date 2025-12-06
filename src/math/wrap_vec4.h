#ifndef LIMB_VEC4_WRAP_H
#define LIMB_VEC4_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newVec4(lua_State *L);
void luaopen_limb_Vec4(lua_State* L);
}

#endif // LIMB_VEC4_WRAP_H
