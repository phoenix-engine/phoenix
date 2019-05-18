#include "SDL.h"

#include "init_error.hpp"
#include "sdl_init_error.hpp"

namespace phx_err {

    SDLInitError::SDLInitError()
        : SDLInitError("SDL initialization error") {}

    SDLInitError::SDLInitError(std::stringstream& ss)
        : SDLInitError(std::move(ss.str())) {}

    SDLInitError::SDLInitError(std::string&& s)
        : InitError(std::move(s)) {
	message.append(": ").append(SDL_GetError());
    }

} // namespace phx_err
