#include "SDL.h"

#include "event.hpp"
#include "input.hpp"
#include "phx_sdl/sdl_input.hpp"

namespace phx_sdl {

    template <typename Consumer>
    void Input<Consumer>::poll() noexcept {
	SDL_Event e;
	while (true) {
	    while (SDL_PollEvent(&e)) {
		switch (e.type) {

		/* Keyboard events */
		case SDL_KEYDOWN:
		    if (e.key.keysym.sym == SDLK_q) {
			into.quit_command();
			return;
		    }
		    break;
		// case SDL_KEYUP           /**< Key released */

		/* Mouse events */
		case SDL_MOUSEMOTION:
		    into.move_intent(e.motion.x, e.motion.y);
		    break;

		case SDL_MOUSEBUTTONDOWN:
		    into.set_intent(e.button.x, e.button.y, true);
		    break;

		case SDL_MOUSEBUTTONUP:
		    into.set_intent(e.button.x, e.button.y, false);
		    break;

		    // case SDL_MOUSEWHEEL      /**< Mouse wheel motion

		default:
		    // Uh oh, I haven't thought about this
		    break;
		}
	    }
	}
    }

    template <typename Consumer>
    Input<Consumer>::Input(input::Input<Consumer>& with) noexcept
        : into(with){};

} // namespace phx_sdl