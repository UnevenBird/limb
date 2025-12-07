#ifndef LIMB_MESH_WRAP_H
#define LIMB_MESH_WRAP_H

#include "common/luax.h"
#include "graphics/mesh.h"

extern "C" {
	int w_newMesh(lua_State *L);
	int luaopen_limb_Mesh(lua_State* L);
}

namespace limb::graphics {
	inline Mesh* luax_checkmesh(lua_State* L, int idx) {
		return luax_checkuserdata<Mesh>(L, idx, "Mesh");
	}
}

#endif // LIMB_MESH_WRAP_H
