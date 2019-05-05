#include "SDL.h"

#include "sdl_init_error.hpp"

namespace err {

    SDLInitError::SDLInitError() : InitError() {
	msg.append(SDL_GetError());
    }

} // namespace err
