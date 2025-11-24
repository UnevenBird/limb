#include "graphics/wrap_texture.h"

extern "C" int w_newTexture(lua_State *L) {
	std::string path = luax_checkstring(L, 1);
	return 0;
}
