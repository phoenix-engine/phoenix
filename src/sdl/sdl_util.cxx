#include <sstream>
#include <string>

#include "display.hpp"
#include "init_error.hpp"
#include "sdl_util.hpp"

namespace sdl {
    SDLUtil::SDLUtil(const std::string& titleIn, Uint32 windowFlags,
                     Uint32 SDLSubsystems) noexcept(false)
        : title(titleIn), initVideo(),
          window(title.c_str(), SDL_WINDOWPOS_CENTERED,
                 SDL_WINDOWPOS_CENTERED, display.w(), display.h(),
                 windowFlags),
          initUtil(SDLSubsystems) {

	window.show();
    }
}; // namespace sdl
