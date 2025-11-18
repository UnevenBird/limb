#ifndef LIMB_EVENT_H
#define LIMB_EVENT_H
#define RGFW_IMPORT

#include "window/window.h"
#include <string>
#include <queue>

namespace limb {

enum class EventType {
	None = 0, /*!< no event has been sent */
	Quit = 1, /*!< the user clicked the quit button */
	KeyDown, /* a key has been pressed */
	KeyUp, /*!< a key has been released */
	MouseDown, /*!< a mouse button has been pressed (left,middle,right) */
	MouseUp, /*!< a mouse button has been released (left,middle,right) */
	MouseWheel, /*!< a mouse scroll event */
	MouseMoved, /*!< the position of the mouse has been changed */
	MouseEnter, /* mouse entered the window */
	MouseLeave, /* mouse left the window */
	WindowMoved, /*!< the window was moved (by the user) */
	WindowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	WindowFocus, /*!< window is in focus now */
	WindowUnfocus, /*!< window is out of focus now */
	// WindowRefresh, /* The window content needs to be refreshed */
	// WindowDataDrop, /*!< a file has been dropped into the window */
	// WindowDataDrag, /*!< the start of a drag and drop event, when the file is being dragged */
	// WindowMaximized, /*!< the window was maximized */
	// WindowMinimized, /*!< the window was minimized */
	// WindowRestored, /*!< the window was restored */
	// ScaleUpdated /*!< content scale factor changed */
};

struct Event {
	EventType type;
	int x, y;
	float dx, dy;
	bool repeat;
	std::string key;
	u8 btn;
};

inline std::deque<Event> event_queue;

void PumpEvents();
bool PollEvent(Event &event);

constexpr const char* EventTypeToString(EventType type) {
	switch (type) {
		case EventType::None: return "none";
		case EventType::Quit: return "quit";
		case EventType::KeyDown: return "key_down";
		case EventType::KeyUp: return "key_up";
		case EventType::MouseDown: return "mouse_down";
		case EventType::MouseUp: return "mouse_up";
		case EventType::MouseMoved: return "mouse_move";
		case EventType::MouseWheel: return "mouse_wheel";
		case EventType::MouseEnter: return "mouse_enter";
		case EventType::MouseLeave: return "mouse_leave";
		case EventType::WindowMoved: return "window_move";
		case EventType::WindowResized: return "window_resize";
		case EventType::WindowFocus: return "window_focus";
		case EventType::WindowUnfocus: return "window_unfocus";
		default: return "unknown";
	}
}

constexpr const char* EventKeyToString(u8 key) {
	switch(key) {
		case RGFW_keyNULL: return "null";
		case RGFW_escape: return "escape";
		case RGFW_backtick: return "`";
		case RGFW_0: return "0";
		case RGFW_1: return "1";
		case RGFW_2: return "2";
		case RGFW_3: return "3";
		case RGFW_4: return "4";
		case RGFW_5: return "5";
		case RGFW_6: return "6";
		case RGFW_7: return "7";
		case RGFW_8: return "8";
		case RGFW_9: return "9";
		case RGFW_minus: return "-";
		case RGFW_equals: return "=";
		case RGFW_backSpace: return "backspace";
		case RGFW_tab: return "tab";
		case RGFW_space: return "space";
		case RGFW_a: return "a";
		case RGFW_b: return "b";
		case RGFW_c: return "c";
		case RGFW_d: return "d";
		case RGFW_e: return "e";
		case RGFW_f: return "f";
		case RGFW_g: return "g";
		case RGFW_h: return "h";
		case RGFW_i: return "i";
		case RGFW_j: return "j";
		case RGFW_k: return "k";
		case RGFW_l: return "l";
		case RGFW_m: return "m";
		case RGFW_n: return "n";
		case RGFW_o: return "o";
		case RGFW_p: return "p";
		case RGFW_q: return "q";
		case RGFW_r: return "r";
		case RGFW_s: return "s";
		case RGFW_t: return "t";
		case RGFW_u: return "u";
		case RGFW_v: return "v";
		case RGFW_w: return "w";
		case RGFW_x: return "x";
		case RGFW_y: return "y";
		case RGFW_z: return "z";
		case RGFW_period: return ".";
		case RGFW_comma: return ",";
		case RGFW_slash: return "/";
		case RGFW_bracket: return "[";
		case RGFW_closeBracket: return "]";
		case RGFW_semicolon: return ";";
		case RGFW_apostrophe: return "'";
		case RGFW_backSlash: return "\\";
		case RGFW_return: return "return";
		case RGFW_delete: return "delete";
		case RGFW_F1: return "f1";
		case RGFW_F2: return "f2";
		case RGFW_F3: return "f3";
		case RGFW_F4: return "f4";
		case RGFW_F5: return "f5";
		case RGFW_F6: return "f6";
		case RGFW_F7: return "f7";
		case RGFW_F8: return "f8";
		case RGFW_F9: return "f9";
		case RGFW_F10: return "f10";
		case RGFW_F11: return "f11";
		case RGFW_F12: return "f12";
		case RGFW_F13: return "f13";
		case RGFW_F14: return "f14";
		case RGFW_F15: return "f15";
		case RGFW_F16: return "f16";
		case RGFW_F17: return "f17";
		case RGFW_F18: return "f18";
		case RGFW_F19: return "f19";
		case RGFW_F20: return "f20";
		case RGFW_F21: return "f21";
		case RGFW_F22: return "f22";
		case RGFW_F23: return "f23";
		case RGFW_F24: return "f24";
		case RGFW_F25: return "f25";
		case RGFW_capsLock: return "caps";
		case RGFW_shiftL: return "lshift";
		case RGFW_controlL: return "lctrl";
		case RGFW_altL: return "lalt";
		case RGFW_superL: return "lsuper";
		case RGFW_shiftR: return "rshift";
		case RGFW_controlR: return "rcontrol";
		case RGFW_altR: return "ralt";
		case RGFW_superR: return "rsuper";
		case RGFW_up: return "up";
		case RGFW_down: return "down";
		case RGFW_left: return "left";
		case RGFW_right: return "right";
		case RGFW_insert: return "insert";
		case RGFW_menu: return "menu";
		case RGFW_end: return "end";
		case RGFW_home: return "home";
		case RGFW_pageUp: return "pageup";
		case RGFW_pageDown: return "pagedown";
		case RGFW_numLock: return "numlock";
		case RGFW_kpSlash: return "num/";
		case RGFW_kpMultiply: return "num*";
		case RGFW_kpPlus: return "num+";
		case RGFW_kpMinus: return "num-";
		case RGFW_kpEqual: return "num=";
		case RGFW_kp1: return "num1";
		case RGFW_kp2: return "num2";
		case RGFW_kp3: return "num3";
		case RGFW_kp4: return "num4";
		case RGFW_kp5: return "num5";
		case RGFW_kp6: return "num6";
		case RGFW_kp7: return "num7";
		case RGFW_kp8: return "num8";
		case RGFW_kp9: return "num9";
		case RGFW_kp0: return "num0";
		case RGFW_kpPeriod: return "num.";
		case RGFW_kpReturn: return "numreturn";
		case RGFW_scrollLock: return "scrolllock";
		case RGFW_printScreen: return "printscreen";
		case RGFW_pause: return "pause";
		case RGFW_world1: return "world1";
		case RGFW_world2: return "world2";
		default: return "unknown";
	}

	return 0;
}

} // namespace limb

#endif // LIMB_EVENT_H
