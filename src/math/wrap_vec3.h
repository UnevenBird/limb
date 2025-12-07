#ifndef LIMB_VEC3_WRAP_H
#define LIMB_VEC3_WRAP_H

#include "common/luax.h"
#include "glm/vec3.hpp"

extern "C" {
	int w_newVec3(lua_State *L);
	void luaopen_limb_Vec3(lua_State* L);
}

namespace limb::math {
	inline glm::vec3* luax_checkvec3(lua_State* L, int idx) {
		return luax_checkuserdata<glm::vec3>(L, idx, "Vec3");
	}
}

#endif // LIMB_VEC3_WRAP_H
