#include "graphics/shader.h"
#include "graphics/wrap_shader.h"

extern "C" int w_newShader(lua_State *L) {
	std::string vertex_code = luax_checkstring(L, 1);
	std::string fragment_code = luax_checkstring(L, 2);

	void* ud = lua_newuserdata(L, sizeof(limb::graphics::Shader));
	limb::graphics::Shader* shader = new(ud) limb::graphics::Shader();

	auto result = shader->Init(vertex_code, fragment_code);
	if (!result) {
		shader->~Shader();
		return luaL_error(L, "Error: %s", result.error().c_str());
	}

	luaL_getmetatable(L, "Shader");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_gc(lua_State *L) {
	auto* shader = luax_checkuserdata<limb::graphics::Shader>(L, 1, "Shader");
	shader->~Shader();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* shader = luax_checkuserdata<limb::graphics::Shader>(L, 1, "Shader");
	lua_pushfstring(L, "Shader (%p)", shader);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void register_Shader(lua_State* L) {
	luaL_newmetatable(L, "Shader");
	luax_setfuncs(L, functions);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}