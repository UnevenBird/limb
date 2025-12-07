#ifndef LIMB_SHADER_WRAP_H
#define LIMB_SHADER_WRAP_H

#include "common/luax.h"
#include "graphics/shader.h"

extern "C" {
	int w_newShader(lua_State *L);
	int luaopen_limb_Shader(lua_State* L);
}

namespace limb::graphics {
	inline Shader* luax_checkshader(lua_State* L, int idx) {
		return luax_checkuserdata<Shader>(L, idx, "Shader");
	}
}

#endif // LIMB_SHADER_WRAP_H
