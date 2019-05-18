#ifndef PHX_SDL_GLRENDERER_H
#define PHX_SDL_GLRENDERER_H

#include <functional>

#include <glad/glad.h>

#include "SDL.h"

#include "graphics.hpp"

namespace phx_sdl {

    class GLRenderer {
    public:
	GLRenderer(SDL_Window*, int w, int h) noexcept(false);

	static const Uint32 windowFlags() noexcept(true);
	static const Uint32 sdlDefaults() noexcept(true);
	static void         postHooks() noexcept(true);

	void clear();
	void update();
	void draw(std::nullptr_t);

	void drawPoint(int x, int y, int color);

	~GLRenderer();

    private:
	SDL_GLContext context;
	SDL_Window*   window;

	GLuint program;
	GLuint vao;
	GLuint vbo;
    };

} // namespace phx_sdl

#endif
