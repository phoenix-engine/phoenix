#include "phx_sdl/window.hpp"
#include "init_error.hpp"
#include "sdl_init_error.hpp"

#include "SDL.h"

namespace phx_sdl {

    namespace {

	void destroy(SDL_Window* w) {
	    SDL_DestroyWindow(w);
	    SDL_Quit();
	}

    } // namespace

    Window::Window(std::string title, int x, int y, int w, int h,
                   Uint32 flags) noexcept(false)
        : title(title),
          window(SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) {
	if (window == nullptr) {
	    throw phx_err::SDLInitError("SDL_CreateWindow failed");
	}
    }

    Window::operator SDL_Window*() const { return window; }

    const char* Window::get_title() const { return title.c_str(); }

    void Window::show() { SDL_ShowWindow(window); }

}; // namespace phx_sdl
