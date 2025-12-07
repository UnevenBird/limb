#ifndef LIMB_TEXTURE_WRAP_H
#define LIMB_TEXTURE_WRAP_H

#include "common/luax.h"
#include "graphics/texture.h"

extern "C" {
	int w_newTexture(lua_State *L);
	int luaopen_limb_Texture(lua_State* L);
}

namespace limb::graphics {
	inline Texture* luax_checktexture(lua_State* L, int idx) {
		return luax_checkuserdata<Texture>(L, idx, "Texture");
	}
}

#endif // LIMB_TEXTURE_WRAP_H
