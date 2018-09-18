#ifndef PHX_SDLRENDERER_H
#define PHX_SDLRENDERER_H

#include "SDL.h"

#include "texture.hpp"

namespace sdl {
    class Renderer {
    public:
	Renderer(SDL_Window*, int w, int h) noexcept(false);

	void update();
	void draw();
	void clear();

	void drawPoint(int x, int y, int color);

	~Renderer();

    private:
	int           w, h;
	SDL_Renderer* renderer;
	Uint32*       pixels;
	sdl::Texture  texture;
    };
} // namespace sdl

#endif
