#include <sstream>

#include <glad/glad.h>

#include "SDL.h"

#include "gl_renderer.hpp"
#include "init_error.hpp"

namespace sdl {
    GLRenderer::GLRenderer(SDL_Window* win, int w,
                           int h) noexcept(false) {
	context = SDL_GL_CreateContext(win);
	if (context == NULL) {
	    std::stringstream ss;
	    ss << "SDL_GL_CreateContext failed: " << SDL_GetError();
	    throw err::InitError(ss);
	}

	int gladInitOk = gladLoadGLLoader(
	  (GLADloadproc)SDL_GL_GetProcAddress);
	if (!gladInitOk) {
	    std::stringstream ss;
	    ss << "gladLoadGLLoader failed: " << gladInitOk;
	    throw err::InitError(ss);
	}

	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
    }

    void GLRenderer::update() {}
    void GLRenderer::draw() {}
    void GLRenderer::clear() {}

    void GLRenderer::drawPoint(int x, int y, int color) {}

    GLRenderer::~GLRenderer() { SDL_GL_DeleteContext(context); }
}; // namespace sdl
