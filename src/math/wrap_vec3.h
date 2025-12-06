#ifndef LIMB_VEC3_WRAP_H
#define LIMB_VEC3_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newVec3(lua_State *L);
void register_Vec3(lua_State* L);
}

#endif // LIMB_VEC3_WRAP_H
