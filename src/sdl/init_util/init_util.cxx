#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "phx_sdl/init_util.hpp"

namespace phx_sdl {

    InitUtil::InitUtil(Uint32 flags) noexcept(false) {
	if (int initOk = SDL_Init(flags) != 0) {
	    std::stringstream ss;
	    ss << "SDL_Init failed with code " << initOk << ": "
	       << SDL_GetError();
	    throw phx_err::InitError(ss);
	}
    }

    InitUtil::~InitUtil() { SDL_Quit(); }

}; // namespace phx_sdl
