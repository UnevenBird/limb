#include "graphics/mesh.h"
#include "graphics/wrap_mesh.h"

#include <vector>

extern "C" int w_newMesh(lua_State *L) {
	if (!lua_istable(L, 1) || !lua_istable(L, 2)) {
		return luaL_error(L, "Error!!!");
	}

	int vertex_count = static_cast<int> (lua_objlen(L, 1));
	std::vector<float> vertices;
	vertices.reserve(vertex_count);
	for (int i = 1; i <= vertex_count; ++i) {
        lua_rawgeti(L, 1, i);
        if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			return luaL_error(L, "bad argument #%d (number expected)", i);
        }
		vertices.push_back(static_cast<float>(lua_tonumber(L, -1)));
        lua_pop(L, 1);
    }

	int index_count = static_cast<int> (lua_objlen(L, 2));
	std::vector<unsigned int> indices;
	indices.reserve(index_count);
	for (int i = 1; i <= index_count; ++i) {
        lua_rawgeti(L, 2, i);
        if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			return luaL_error(L, "bad argument #%d (number expected)", i);
        }
		indices.push_back(static_cast<unsigned int>(lua_tointeger(L, -1)));
        lua_pop(L, 1);
    }

	void* ud = lua_newuserdata(L, sizeof(limb::graphics::Mesh));
	limb::graphics::Mesh* mesh = new(ud) limb::graphics::Mesh();

	auto result = mesh->Init(vertices, indices);
	if (!result) {
		mesh->~Mesh();
		return luaL_error(L, "Error: %s", result.error().c_str());
	}

	luaL_getmetatable(L, "Mesh");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_render(lua_State *L) {
	auto* mesh = luax_checkuserdata<limb::graphics::Mesh>(L, 1, "Mesh");
	mesh->Render();
	return 0;
}

static int w_gc(lua_State *L) {
	auto* mesh = luax_checkuserdata<limb::graphics::Mesh>(L, 1, "Mesh");
	mesh->~Mesh();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* mesh = luax_checkuserdata<limb::graphics::Mesh>(L, 1, "Mesh");
	lua_pushfstring(L, "Mesh (%p)", mesh);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "render", w_render },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void register_Mesh(lua_State* L) {
	luaL_newmetatable(L, "Mesh");
	luax_setfuncs(L, functions);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}