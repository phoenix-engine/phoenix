#ifndef PHX_SDL_WINDOW_H
#define PHX_SDL_WINDOW_H

#include <string>

#include "lifetime.hpp"

#include "SDL.h"

namespace phx_sdl {

    namespace {

	void destroy(SDL_Window*);

	using WindowKeeper = phx::ResourceKeeper<SDL_Window, destroy>;

    } // namespace

    class Window {
    public:
	Window(std::string title = "Phoenix app",
	       int         x     = SDL_WINDOWPOS_CENTERED,
	       int y = SDL_WINDOWPOS_CENTERED, int w = 640, int h = 480,
	       Uint32 flags = 0) noexcept(false);

	Window(Window&&) = default;

	operator SDL_Window*() const;

	void        show();
	const char* get_title() const;

    private:
	WindowKeeper window;

	std::string title;
    };

} // namespace phx_sdl

#endif
