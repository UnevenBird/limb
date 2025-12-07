#include "graphics/wrap_mesh.h"

#include <vector>

static void parse_layout(lua_State *L, int idx, limb::graphics::VertexLayout& layout) {
	int count = lua_objlen(L, idx);
	unsigned int size = 0;
	for (int i = 1; i <= count; ++i) {
		lua_rawgeti(L, idx, i);
		if (!lua_istable(L, -1)) {
			lua_pop(L, 1);
			luaL_error(L, "Attribute #%d must be a table", i);
			return;
		}

		lua_getfield(L, -1, "location");
		if (!lua_isnumber(L, -1)) {
			luaL_error(L, "Attribute #%d: 'location' must be an integer", i);
			return;
		}
		unsigned int location = static_cast<unsigned int>(lua_tointeger(L, -1));
		lua_pop(L, 1);

		lua_getfield(L, -1, "type");
		if (!lua_isstring(L, -1)) {
			luaL_error(L, "Attribute #%d: 'type' must be a string", i);
			return;
		}
		std::string attr_type = luax_checkstring(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "components");
		if (!lua_isnumber(L, -1)) {
			luaL_error(L, "Attribute #%d: 'components' must be an integer", i);
			return;
		}
		int components = static_cast<int>(lua_tointeger(L, -1));
		lua_pop(L, 1);

		GLenum type;
		if (attr_type.compare("float") == 0) {
			type = GL_FLOAT;
		} else {
			luaL_error(L, "Attribute #%d: unknown attribute type: %s", i, attr_type.c_str());
			return;
		}

		unsigned int offset = size * sizeof(float);
		layout.attributes.emplace_back(limb::graphics::VertexAttribute {
			.location = location,
			.components = components,
			.type = type,
			.normalized = GL_FALSE,
			.offset = offset
		});
		size += components;
		lua_pop(L, 1);
	}

	GLsizei total_stride = 0;
	// GLuint total_components = 0;
	for(auto &attr : layout.attributes) {
		GLsizei type_size = 0;
		if (attr.type == GL_FLOAT) {
			type_size = sizeof(GLfloat);
		}
		total_stride += attr.components * type_size;
		// total_components += attr.components;
	}
	layout.stride = total_stride;
	// layout.components = total_components;
}

extern "C" int w_newMesh(lua_State *L) {
	if (!lua_istable(L, 1)) return luax_typerror(L, 1, "table");
	if (!lua_istable(L, 2)) return luax_typerror(L, 2, "table");
	if (!lua_istable(L, 3)) return luax_typerror(L, 3, "table");

	limb::graphics::VertexLayout layout;
	parse_layout(L, 1, layout);

	int vertex_len = lua_objlen(L, 2);
	std::vector<float> vertex_data;
	vertex_data.reserve(vertex_len);
	for (int i = 1; i <= vertex_len; ++i) {
		lua_rawgeti(L, 2, i);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			return luax_tabletyperror(L, 2, i, "number");
		}
		vertex_data.push_back(static_cast<float>(lua_tonumber(L, -1)));
		lua_pop(L, 1);
	}

	int index_count = lua_objlen(L, 3);
	std::vector<unsigned int> indices;
	indices.reserve(index_count);
	for (int i = 1; i <= index_count; ++i) {
		lua_rawgeti(L, 3, i);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			return luax_tabletyperror(L, 3, i, "number");
		}
		indices.push_back(static_cast<unsigned int>(lua_tointeger(L, -1)));
		lua_pop(L, 1);
	}

	void* ud = lua_newuserdata(L, sizeof(limb::graphics::Mesh));
	limb::graphics::Mesh* mesh = new(ud) limb::graphics::Mesh();

	auto result = mesh->Init(layout, vertex_data, indices);
	if (!result) {
		mesh->~Mesh();
		return luaL_error(L, "Error: %s", result.error().c_str());
	}

	luaL_getmetatable(L, "Mesh");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_gc(lua_State *L) {
	auto* mesh = limb::graphics::luax_checkmesh(L, 1);
	mesh->~Mesh();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* mesh = limb::graphics::luax_checkmesh(L, 1);
	lua_pushfstring(L, "Mesh (%p)", mesh);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_Mesh(lua_State* L) {
	luax_register_type(L, "Mesh", functions);
	return 0;
}
