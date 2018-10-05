#ifndef PHX_SDL_GLRENDERER_H
#define PHX_SDL_GLRENDERER_H

#include <functional>

#include <glad/glad.h>

#include "SDL.h"

#include "../graphics/graphics.hpp"

namespace sdl {
    class GLRenderer {
    public:
	GLRenderer(SDL_Window*, int w, int h) noexcept(false);

	static const Uint32 windowFlags() noexcept(true);
	static const Uint32 sdlDefaults() noexcept(true);
	static void         postHooks() noexcept(true);

	void update();
	void draw();
	void clear();

	void drawPoint(int x, int y, int color);

	~GLRenderer();

    private:
	SDL_GLContext context;
	SDL_Window*   window;

	GLuint program;
	GLuint vao;
	GLuint vbo;
    };
} // namespace sdl

#endif
