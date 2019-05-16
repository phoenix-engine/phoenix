#ifndef PHX_SDL_WINDOW_H
#define PHX_SDL_WINDOW_H

#include "SDL.h"

namespace phx_sdl {

    class Window {
    public:
	Window(const char* title = "Phoenix app",
	       int         x     = SDL_WINDOWPOS_CENTERED,
	       int y = SDL_WINDOWPOS_CENTERED, int w = 640, int h = 480,
	       Uint32 flags = 0) noexcept(false);

	SDL_Window* handle() const;

	void        show();
	const char* get_title() const;

	~Window();

    private:
	SDL_Window* window;
	std::string title;
    };

} // namespace phx_sdl

#endif
