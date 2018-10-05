#include <sstream>

#include <glad/glad.h>

#include "SDL.h"

#include "gl_renderer.hpp"
#include "helper.hpp"
#include "init_error.hpp"

namespace sdl {
    float points[] = { 0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
	               0.0f, -0.5f, -0.5f, 0.0f };

    const char* vertex_shader = R"(
#version 400
in vec3 vp;
void main() {
  gl_Position = vec4(vp, 1.0);
})";

    const char* fragment_shader =
      R"(
#version 400
out vec4 frag_colour;
void main() {
  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);
})";

    int getGLAttr(const SDL_GLattr what) noexcept(false) {
	int into = 0;
	if (SDL_GL_GetAttribute(what, &into)) {
	    std::stringstream ss;
	    ss << "Failed to get attribute " << what << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}

	return into;
    }

    const Uint32 GLRenderer::windowFlags() noexcept(true) {
	return SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN |
	       SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL |
	       SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_INPUT_FOCUS |
	       SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS;
    }

    const Uint32 GLRenderer::sdlDefaults() noexcept(true) {
	return SDL_INIT_AUDIO | SDL_INIT_VIDEO;
    }

    void GLRenderer::postHooks() noexcept(true) {
	printf("Configuring SDL for OpenGL 4.1\n");
	Helper::glPostHooks();
    }

    GLRenderer::GLRenderer(SDL_Window* win, int w,
                           int h) noexcept(false)
        : context(SDL_GL_CreateContext(win)), window(win) {

	if (context == NULL) {
	    std::stringstream ss;
	    ss << "SDL_GL_CreateContext failed: " << SDL_GetError();
	    throw err::InitError(ss);
	}

	auto loader     = (GLADloadproc)SDL_GL_GetProcAddress;
	int  gladInitOk = gladLoadGLLoader(loader);

	if (!gladInitOk) {
	    std::stringstream ss;
	    ss << "gladLoadGLLoader failed: " << gladInitOk;
	    throw err::InitError(ss);
	}

	auto glVMaj = getGLAttr(SDL_GL_CONTEXT_MAJOR_VERSION);
	auto glVMin = getGLAttr(SDL_GL_CONTEXT_MINOR_VERSION);

	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	printf("SDL OpenGL API loaded: %d.%d\n", glVMaj, glVMin);

	// WIP: Mess with working shaders

	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points,
	             GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);
    }

    void GLRenderer::update() {}

    void GLRenderer::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(window);
    }

    void GLRenderer::clear() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderer::drawPoint(int x, int y, int color) {}

    GLRenderer::~GLRenderer() { SDL_GL_DeleteContext(context); }
}; // namespace sdl
