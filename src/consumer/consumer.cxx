#include <variant>

#include "event.hpp"
#include "input.hpp"
#include "queue.hpp"

namespace input {

    // Make a singleton in case that's what the user wants.
    Simple simple = Simple();

    Consumer<Simple>* Simple::reset(input::Input<Simple>* in) noexcept {
	intent = false;
	return this;
    }

    Consumer<Simple>*
    Simple::consume(input::Input<Simple>*       in,
                    event::Queue<event::Event>& eq) noexcept {

	auto x_in = in->x;
	auto y_in = in->y;

	auto had_intent  = intent;
	auto has_intent  = in->intent;
	auto wants_quit  = in->wants_quit;
	auto wants_pause = in->toggle_pause;

	if (wants_quit) {
	    // User wants to quit.
	    eq.enqueue(event::EventWantsQuit{});
	} else if (!had_intent && has_intent) {
	    // If intent changed from no to yes, send EventIntent and
	    // start tracking first position.
	    auto begin = event::EventIntent{ x_in, y_in };
	    eq.enqueue(begin);
	    box_begin = begin;
	} else if (had_intent && has_intent) {
	    // Dragging.
	    eq.enqueue(event::EventIntent{ x_in, y_in });
	    eq.enqueue(event::EventDraggingBox{ box_begin.x, x_in,
	                                        box_begin.y, y_in });
	} else if (had_intent && !has_intent) {
	    // Finished dragging.
	    eq.enqueue(event::EventLostIntent{ x_in, y_in });
	    eq.enqueue(event::EventFinishedBox{ box_begin.x, x_in,
	                                        box_begin.y, y_in });
	} else if (!had_intent && !has_intent) {
	    // Why did the Consumer get invoked??
	}

	return this;
    }

}; // namespace input
