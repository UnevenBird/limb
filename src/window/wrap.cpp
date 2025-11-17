#include "window/wrap.h"
#include "window/window.h"

static int w_create(lua_State *L) {
	std::string title = luax_checkstring(L, 1);
	int width = luaL_checkinteger(L, 2);
	int height = luaL_checkinteger(L, 3);
	limb::window = new limb::Window(title, width, height);

	if (!limb::window->Init()) {
		delete limb::window;
		limb::window = nullptr;
		return luaL_error(L, "Failed to initialize window.");
	}

	return 0;
}

static int w_close(lua_State *L) {
	if (limb::window) {
		delete limb::window;
		limb::window = nullptr;
	}
	return 0;
}

static const luaL_Reg functions[] = {
	{ "create", w_create },
	{ "close", w_close },
	{ nullptr, nullptr }
};

extern "C" int luaopen_limb_window(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}