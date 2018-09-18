#ifndef PHX_SDLWINDOW_H
#define PHX_SDLWINDOW_H

#include "SDL.h"

#include "renderer.hpp"

namespace sdl {
    class Window {
    public:
	Window(const char* title = "SDL Window",
	       int         x     = SDL_WINDOWPOS_CENTERED,
	       int y = SDL_WINDOWPOS_CENTERED, int w = 640, int h = 480,
	       Uint32 flags = 0) noexcept(false);

	SDL_Window* handle();

	void show();

	~Window();

    private:
	SDL_Window* window;
    };
} // namespace sdl

#endif
