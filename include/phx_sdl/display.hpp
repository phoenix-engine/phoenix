#ifndef PHX_SDL_DISPLAY_H
#define PHX_SDL_DISPLAY_H

#include "SDL.h"

namespace phx_sdl {

    class Display {
    public:
	Display() noexcept(false);

	int w() { return display.w; };
	int h() { return display.h; };

	const SDL_DisplayMode* handle();

    private:
	SDL_DisplayMode display;
    };

} // namespace phx_sdl

#endif
