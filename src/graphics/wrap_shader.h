#ifndef LIMB_SHADER_WRAP_H
#define LIMB_SHADER_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newShader(lua_State *L);
void luaopen_limb_Shader(lua_State* L);
}

#endif // LIMB_SHADER_WRAP_H
