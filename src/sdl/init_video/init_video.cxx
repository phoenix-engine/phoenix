#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "phx_sdl/init_video.hpp"

namespace phx_sdl {

    InitVideo::InitVideo() noexcept(false) {
	if (SDL_GetNumVideoDrivers() == 0) {
	    std::stringstream ss;
	    ss << "0 drivers found";
	    throw phx_err::InitError(ss);
	}

	if (int v = SDL_VideoInit(NULL) != 0) {
	    std::stringstream ss;
	    ss << "SDL_VideoInit failed with code " << v << ": "
	       << SDL_GetError();
	    throw phx_err::InitError(ss);
	}

	if (int numDisp = SDL_GetNumVideoDisplays() < 1) {
	    std::stringstream ss;
	    ss << "SDL_GetNumVideoDisplays returned " << numDisp;
	    throw phx_err::InitError(ss);
	}
    }

}; // namespace phx_sdl
