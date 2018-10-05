#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "init_video.hpp"

namespace sdl {
    InitVideo::InitVideo() noexcept(false) {
	if (SDL_GetNumVideoDrivers() == 0) {
	    std::stringstream ss;
	    ss << "0 drivers found";
	    throw err::InitError(ss);
	}

	if (int v = SDL_VideoInit(NULL) != 0) {
	    std::stringstream ss;
	    ss << "SDL_VideoInit failed with code " << v << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}

	if (int numDisp = SDL_GetNumVideoDisplays() < 1) {
	    std::stringstream ss;
	    ss << "SDL_GetNumVideoDisplays returned " << numDisp;
	    throw err::InitError(ss);
	}
    }
}; // namespace sdl
