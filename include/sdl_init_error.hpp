#ifndef PHX_SDL_INIT_ERROR_HPP
#define PHX_SDL_INIT_ERROR_HPP

#include "init_error.hpp"

namespace phx_err {

    class SDLInitError : public InitError {
    public:
	SDLInitError();
	SDLInitError(std::string&& s);
	SDLInitError(std::stringstream& ss);
    };

} // namespace phx_err

#endif // PHX_SDL_INIT_ERROR_HPP
