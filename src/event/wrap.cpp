#include "event/wrap.h"
#include "event/event.h"

static int w_pump(lua_State *L) {
	limb::PumpEvents();
	return 0;
}

static int w_poll(lua_State *L) {
	lua_pushcfunction(L, [](lua_State *L) -> int {
		limb::Event event;
		if (!limb::PollEvent(event))
			return 0;

		lua_pushstring(L, limb::EventTypeToString(event.type));

		switch (event.type) {
		case limb::EventType::Quit:
			return 1;
		case limb::EventType::KeyDown:
			lua_pushstring(L, event.key.c_str());
			lua_pushboolean(L, event.repeat);
			return 3;
		case limb::EventType::KeyUp:
			lua_pushstring(L, event.key.c_str());
			lua_pushboolean(L, event.repeat);
			return 3;
		case limb::EventType::MouseDown:
			lua_pushinteger(L, event.btn);
			lua_pushinteger(L, event.x);
			lua_pushinteger(L, event.y);
			return 4;
		case limb::EventType::MouseUp:
			lua_pushinteger(L, event.btn);
			lua_pushinteger(L, event.x);
			lua_pushinteger(L, event.y);
			return 4;
		case limb::EventType::MouseMoved:
			lua_pushinteger(L, event.x);
			lua_pushinteger(L, event.y);
			lua_pushinteger(L, event.dx);
			lua_pushinteger(L, event.dy);
			return 5;
		case limb::EventType::MouseWheel:
			lua_pushinteger(L, event.dx);
			lua_pushinteger(L, event.dy);
			return 3;
		case limb::EventType::MouseEnter:
			return 1;
		case limb::EventType::MouseLeave:
			return 1;
		case limb::EventType::WindowMoved:
			return 1;
		case limb::EventType::WindowResized:
			return 1;
		case limb::EventType::WindowFocus:
			return 1;
		case limb::EventType::WindowUnfocus:
			return 1;
		default:
			return 1;
		}
	});
	lua_pushnil(L);
	lua_pushnil(L);
	return 3;
}

static const luaL_Reg functions[] = {
	{"pump", w_pump},
	{"poll", w_poll},
	{nullptr, nullptr}
};

extern "C" int luaopen_limb_event(lua_State *L) {
	lua_newtable(L);
	luax_setfuncs(L, functions);
	return 1;
}