#include "limb/limb.h"
#include "window/wrap.h"
#include "window/window.h"

static int w_init(lua_State *L) {
	if (limb::app::HasWindow()) {
		return luaL_error(L, "window already exist!");
	}

	std::string title = luax_checkstring(L, 1);
	int width = luaL_checkinteger(L, 2);
	int height = luaL_checkinteger(L, 3);

	auto result = limb::app::InitWindow(title, width, height);
	if (!result) {
		return luaL_error(L, result.error().c_str());
	}
	return 0;
}

static int w_setVisible(lua_State *L) {
	bool state = lua_toboolean(L, 1);
	limb::app::window->SetVisible(state);
	return 0;
}

static int w_close(lua_State *L) {
	if (!limb::app::HasWindow()) {
		return luaL_error(L, "Failed to close window.");
	}

	delete limb::app::window;
	limb::app::window = nullptr;
	return 0;
}

static int w_opened(lua_State *L) {
	lua_pushboolean(L, limb::app::window != nullptr);
	return 1;
}

static int w_setTitle(lua_State *L) {
	std::string title = luax_checkstring(L, 1);
	limb::app::window-> SetTitle(title);
	return 0;
}

static int w_isVisible(lua_State *L) {
	bool visible = false;
	if (limb::app::HasWindow()) {
		visible = limb::app::window->IsVisible();
	}

	lua_pushboolean(L, visible);
	return 1;
}

static const luaL_Reg functions[] = {
	{ "init", w_init },
	{ "close", w_close },
	{ "opened", w_opened },
	{ "setTitle", w_setTitle },
	{ "setVisible", w_setVisible },
	{ "isVisible", w_isVisible },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_window(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}