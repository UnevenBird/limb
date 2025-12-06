#ifndef LIMB_MESH_WRAP_H
#define LIMB_MESH_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newMesh(lua_State *L);
void luaopen_limb_Mesh(lua_State* L);
}

#endif // LIMB_MESH_WRAP_H
