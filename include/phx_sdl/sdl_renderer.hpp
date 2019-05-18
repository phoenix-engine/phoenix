#ifndef PHX_SDL_SDLRENDERER_H
#define PHX_SDL_SDLRENDERER_H

#include "SDL.h"

#include "texture.hpp"

namespace phx_sdl {

    class SDLRenderer {
    public:
	SDLRenderer(SDL_Window*, int w, int h) noexcept(false);

	static const Uint32 windowFlags() noexcept(true);
	static const Uint32 sdlDefaults() noexcept(true);
	static void         postHooks() noexcept(true);

	void update();
	void draw();
	void clear();

	void drawPoint(int x, int y, int color);

	~SDLRenderer();

    private:
	int           w, h;
	SDL_Renderer* renderer;
	Uint32*       pixels;
	Texture       texture;
    };

} // namespace phx_sdl

#endif
