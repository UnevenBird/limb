#include "graphics/wrap.h"
#include "graphics/graphics.h"
#include "common/color.h"

#include "graphics/wrap_shader.h"
#include "graphics/wrap_mesh.h"
#include "graphics/wrap_texture.h"

static int w_clear(lua_State* L) {
	limb::graphics::Clear();
	return 0;
}

static int w_setBackgroundColor(lua_State* L) {
	limb::Color c;
	luax_checkcolor(L, 1, c);
	limb::graphics::SetBackgroundColor(c);
	return 0;
}

static int w_setShader(lua_State* L) {
	if (!lua_isnoneornil(L, 1)) {
		auto* shader = luax_checkuserdata<limb::graphics::Shader>(L, 1, "Shader");
		limb::graphics::BindShader(shader);
	} else {
		limb::graphics::UnbindShader();
	}
	return 0;
}

static int w_setWireframe(lua_State* L) {
	bool state = lua_toboolean(L, 1);
	limb::graphics::SetWireframe(state);
	return 0;
}

static int w_HSVtoRGB(lua_State* L) {
	limb::Color in, out;
	luax_checkcolor(L, 1, in);
	limb::graphics::HSVtoRGB(in, out);

	lua_pushnumber(L, out.r);
	lua_pushnumber(L, out.g);
	lua_pushnumber(L, out.b);
	lua_pushnumber(L, out.a);
	return 4;
}

static int w_present(lua_State* L) {
	limb::graphics::Present();
	return 0;
}

static const luaL_Reg functions[] = {
	{ "clear", w_clear },
	{ "setBackgroundColor", w_setBackgroundColor },
	{ "newShader", w_newShader },
	{ "newMesh", w_newMesh },
	{ "newTexture", w_newTexture },
	{ "setWireframe", w_setWireframe },
	{ "HSVtoRGB", w_HSVtoRGB },
	{ "setShader", w_setShader },
	{ "present", w_present },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_graphics(lua_State *L) {
	register_Shader(L);
	register_Mesh(L);

	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}