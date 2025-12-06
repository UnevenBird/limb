#include "limb/limb.h"
#include "event/event.h"

namespace limb {

void PumpEvents() {
	if (!limb::app::HasWindow()) return;
	event_queue.clear();

	RGFW_window* window = limb::app::window->GetHandler();
	RGFW_event event;
	while (RGFW_window_checkEvent(window, &event)) {
		switch (event.type) {
		case RGFW_quit:
			event_queue.emplace_back(Event {.type = EventType::Quit});
			break;
		case RGFW_keyPressed:
			event_queue.emplace_back(Event {
				.type = EventType::KeyDown,
				.repeat = static_cast<bool>(event.key.repeat),
				.key = std::string(EventKeyToString(event.key.value))
			});
			break;
		case RGFW_keyReleased:
			event_queue.emplace_back(Event {
				.type = EventType::KeyUp,
				.repeat = static_cast<bool>(event.key.repeat),
				.key = std::string(EventKeyToString(event.key.value))
			});
			break;
		case RGFW_mouseButtonPressed:
			event_queue.emplace_back(Event {
				.type = EventType::MouseDown,
				.x = event.mouse.x,
				.y = event.mouse.y,
				.btn = event.button.value
			});
			break;
		case RGFW_mouseButtonReleased:
			event_queue.emplace_back(Event {
				.type = EventType::MouseUp,
				.x = event.mouse.x,
				.y = event.mouse.y,
				.btn = event.button.value
			});
			break;
		case RGFW_mousePosChanged:
			event_queue.emplace_back(Event {
				.type = EventType::MouseMoved,
				.x = event.mouse.x,
				.y = event.mouse.y,
				.dx = event.mouse.vecX,
				.dy = event.mouse.vecY,
			});
			break;
		case RGFW_mouseScroll:
			event_queue.emplace_back(Event {
				.type = EventType::MouseWheel,
				.dx = event.scroll.x,
				.dy = event.scroll.y,
			});
			break;
		case RGFW_mouseEnter:
			event_queue.emplace_back(Event {
				.type = EventType::MouseEnter,
			});
			break;
		case RGFW_mouseLeave:
			event_queue.emplace_back(Event {
				.type = EventType::MouseLeave,
			});
			break;
		case RGFW_windowMoved:
			event_queue.emplace_back(Event {
				.type = EventType::WindowMoved,
			});
			break;
		case RGFW_windowResized: {
			i32 width, height;
			RGFW_window_getSize(window, &width, &height);
			event_queue.emplace_back(Event {
				.type = EventType::WindowResized,
				.x = width,
				.y = height,
			});
			limb::app::window->Resize(width, height);
			break;
		}
		case RGFW_focusIn:
			event_queue.emplace_back(Event {
				.type = EventType::WindowFocus,
			});
			break;
		case RGFW_focusOut:
			event_queue.emplace_back(Event {
				.type = EventType::WindowUnfocus,
			});
			break;
		default:
			event_queue.emplace_back(Event {.type = EventType::None});
			break;
		}
	}
}

bool PollEvent(Event &event) {
	if (event_queue.empty())
		return false;
	
	event = event_queue.front();
	event_queue.pop_front();
	return true;
}

} // namespace limb
