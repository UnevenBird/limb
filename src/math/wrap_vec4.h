#ifndef LIMB_VEC4_WRAP_H
#define LIMB_VEC4_WRAP_H

#include "common/luax.h"
#include "glm/vec4.hpp"

extern "C" {
	int w_newVec4(lua_State *L);
	void luaopen_limb_Vec4(lua_State* L);
}

namespace limb::math {
	inline glm::vec4* luax_checkvec4(lua_State* L, int idx) {
		return luax_checkuserdata<glm::vec4>(L, idx, "Vec4");
	}
}

#endif // LIMB_VEC4_WRAP_H
