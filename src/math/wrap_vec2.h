#ifndef LIMB_VEC2_WRAP_H
#define LIMB_VEC2_WRAP_H

#include "common/luax.h"
#include "glm/vec2.hpp"

extern "C" {
	int w_newVec2(lua_State *L);
	void luaopen_limb_Vec2(lua_State* L);
}

namespace limb::math {
	inline glm::vec2* luax_checkvec2(lua_State* L, int idx) {
		return luax_checkuserdata<glm::vec2>(L, idx, "Vec2");
	}
}

#endif // LIMB_VEC2_WRAP_H
