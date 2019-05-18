#include <iostream>

#include "SDL.h"

#include "init_error.hpp"
#include "phx_sdl/window.hpp"
#include "sdl_init_error.hpp"

namespace phx_sdl {

    Window::Window(const char* title, int x, int y, int w, int h,
                   Uint32 flags) noexcept(false)
        : title(title),
          window(SDL_CreateWindow(title, x, y, w, h, flags)) {
	if (window == NULL) {
	    throw phx_err::SDLInitError("SDL_CreateWindow failed");
	}
    }

    SDL_Window* Window::handle() const { return window; }
    const char* Window::get_title() const { return title.c_str(); }

    void Window::show() { SDL_ShowWindow(window); }

    Window::~Window() { SDL_DestroyWindow(window); }

}; // namespace phx_sdl
