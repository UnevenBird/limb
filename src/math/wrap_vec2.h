#ifndef LIMB_VEC2_WRAP_H
#define LIMB_VEC2_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newVec2(lua_State *L);
void register_Vec2(lua_State* L);
}

#endif // LIMB_VEC2_WRAP_H
