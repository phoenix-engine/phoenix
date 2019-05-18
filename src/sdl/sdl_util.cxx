#include <functional>
#include <string>

#include "SDL.h"

#include "phx_sdl/sdl_util.hpp"

#include "phx_sdl/display.hpp"

namespace phx_sdl {

    SDLUtil::SDLUtil(const std::string& titleIn, Uint32 windowFlags,
                     Uint32                SDLSubsystems,
                     std::function<void()> postHooks) noexcept(false)
        : title(titleIn), initUtil(SDLSubsystems), initVideo(),
          window(title.c_str(), SDL_WINDOWPOS_CENTERED,
                 SDL_WINDOWPOS_CENTERED, display.w(), display.h(),
                 windowFlags) {

	postHooks();

	window.show();
    }

}; // namespace phx_sdl
