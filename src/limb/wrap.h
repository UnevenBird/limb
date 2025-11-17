#ifndef LIMB_WRAP_H
#define LIMB_WRAP_H

#include "common/luax.h"

extern "C" {
int luaopen_limb(lua_State *L);
int luaopen_limb_boot(lua_State *L);
extern int luaopen_limb_window(lua_State *L);
extern int luaopen_limb_timer(lua_State *L);
}

namespace limb {

enum class APP_STATE {
	RUN = 0,
	QUIT = 1,
};

APP_STATE runlimb(APP_STATE &retval);

} // namespace limb

#endif // LIMB_WRAP_H
