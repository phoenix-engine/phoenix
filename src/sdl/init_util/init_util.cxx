#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "init_util.hpp"

namespace sdl {
    InitUtil::InitUtil(Uint32 flags) noexcept(false) {
	if (int initOk = SDL_Init(flags) != 0) {
	    std::stringstream ss;
	    ss << "SDL_Init failed with code " << initOk << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}
    }

    InitUtil::~InitUtil() { SDL_Quit(); }
}; // namespace sdl
