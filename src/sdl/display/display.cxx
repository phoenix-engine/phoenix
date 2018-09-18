#include <sstream>

#include "SDL.h"

#include "display.hpp"
#include "init_error.hpp"

namespace sdl {
    Display::Display() noexcept(false) {
	std::stringstream ss;

	int initOk = SDL_GetCurrentDisplayMode(0, &display);
	if (initOk != 0) {
	    ss << "SDL_GetCurrentDisplayMode failed with code "
	       << initOk << ": " << SDL_GetError();
	    throw err::InitError(ss);
	}
    }
}; // namespace sdl
