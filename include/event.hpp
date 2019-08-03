#ifndef PHX_EVENT_EVENT_HPP
#define PHX_EVENT_EVENT_HPP

#include <variant>

namespace event {

    struct EventWantsQuit {};

    struct EventIntent {
	int x, y;
    };

    struct EventLostIntent : EventIntent {};

    struct EventDraggingBox {
	int x0, x1, y0, y1;
    };

    struct EventFinishedBox : EventDraggingBox {};

    using Event =
      std::variant<EventWantsQuit, EventIntent, EventLostIntent,
                   EventDraggingBox, EventFinishedBox>;

}; // namespace event

#endif // PHX_EVENT_EVENT_HPP
