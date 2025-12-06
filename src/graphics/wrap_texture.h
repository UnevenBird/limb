#ifndef LIMB_TEXTURE_WRAP_H
#define LIMB_TEXTURE_WRAP_H

#include "common/luax.h"

extern "C" {
int w_newTexture(lua_State *L);
void luaopen_limb_Texture(lua_State* L);
}

#endif // LIMB_TEXTURE_WRAP_H
