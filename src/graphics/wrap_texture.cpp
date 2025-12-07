#include "graphics/wrap_texture.h"

extern "C" int w_newTexture(lua_State *L) {
	std::string path = luax_checkstring(L, 1);

	void* ud = lua_newuserdata(L, sizeof(limb::graphics::Texture));
	limb::graphics::Texture* texture = new(ud) limb::graphics::Texture();

	auto result = texture->Init(path);
	if (!result) {
		texture->~Texture();
		return luaL_error(L, "Error: %s", result.error().c_str());
	}

	luaL_getmetatable(L, "Texture");
	lua_setmetatable(L, -2);
	return 1;
}

static int w_getDimensions(lua_State *L) {
	auto* texture = limb::graphics::luax_checktexture(L, 1);
	lua_pushinteger(L, texture->GetWidth());
	lua_pushinteger(L, texture->GetHeight());
	return 2;
}

static int w_gc(lua_State *L) {
	auto* texture = limb::graphics::luax_checktexture(L, 1);
	texture->~Texture();
	return 0;
}

static int w_tostring(lua_State *L) {
	auto* texture = limb::graphics::luax_checktexture(L, 1);
	lua_pushfstring(L, "Texture (%p)", texture);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "getDimensions", w_getDimensions },
	{ "__gc", w_gc },
	{ "__tostring", w_tostring },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_Texture(lua_State* L) {
	luax_register_type(L, "Texture", functions);
	return 0;
}
