#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "phx_sdl/display.hpp"
#include "sdl_init_error.hpp"

namespace phx_sdl {

    Display::Display() noexcept(false) {
	int initOk = SDL_GetCurrentDisplayMode(0, &display);
	if (initOk != 0) {
	    std::stringstream ss;
	    ss << "SDL_GetCurrentDisplayMode failed"
	       << " with code " << initOk;
	    throw phx_err::SDLInitError(ss);
	}
    }

}; // namespace phx_sdl
