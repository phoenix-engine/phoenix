#ifndef PHX_SDL_GLRENDERER_H
#define PHX_SDL_GLRENDERER_H

#include "SDL.h"

namespace sdl {
    class GLRenderer {
    public:
	GLRenderer(SDL_Window*, int w, int h) noexcept(false);

	void update();
	void draw();
	void clear();

	void drawPoint(int x, int y, int color);

	~GLRenderer();

    private:
	SDL_GLContext context;
    };
} // namespace sdl

#endif
