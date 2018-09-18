#include <sstream>
#include <string>

#include "SDL.h"
#include "init_error.hpp"

using namespace err;

InitError::InitError() : exception() { msg.append(unknown); }

InitError::InitError(std::string&& s)
    : exception(), msg(std::forward<std::string>(s)) {}

InitError::InitError(std::stringstream& ss)
    : exception(), msg(ss.str()) {}

const char* InitError::what() const noexcept { return msg.c_str(); }

SDLInitError::SDLInitError() : InitError() {
    msg.append(SDL_GetError());
}
