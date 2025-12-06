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

static int w_send(lua_State *L) {
	auto* shader = luax_checkuserdata<limb::graphics::Shader>(L, 1, "Shader");
	std::string uniform = luax_checkstring(L, 2);
	int type = lua_type(L, 3);

	bool success = false;
	switch (type) {
		case LUA_TNUMBER: {
			float value = luax_checkfloat(L, 3);
			success = shader->SendUniform(uniform, value);
			break;
		}
		case LUA_TUSERDATA: {
			if (luax_isuserdata(L, 3, "Vec2")) {
				auto* vec = luax_checkuserdata<glm::vec2>(L, 3, "Vec2");
				success = shader->SendUniform(uniform, *vec);
			}
			else if (luax_isuserdata(L, 3, "Vec3")) {
				auto* vec = luax_checkuserdata<glm::vec3>(L, 3, "Vec3");
				success = shader->SendUniform(uniform, *vec);
			}
			else if (luax_isuserdata(L, 3, "Vec4")) {
				auto* vec = luax_checkuserdata<glm::vec4>(L, 3, "Vec4");
				success = shader->SendUniform(uniform, *vec);
			} else {
				return luax_typerror(L, 3, "number or vector");
			}
			break;
		}
		default: {
			return luax_typerror(L, 3, "number or vector");
		}
	}

	if (!success) {
		return luaL_error(L, "Failed to set uniform '%s': shader not active or uniform doesn't exist.", uniform.c_str());
	}
	return 0;
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
	{ "send", w_send },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" void luaopen_limb_Shader(lua_State* L) {
	luax_register_type(L, "Shader", functions);
}
