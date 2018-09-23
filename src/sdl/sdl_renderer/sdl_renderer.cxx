#include <cstring>
#include <sstream>

#include <glad/glad.h>

#include "SDL.h"

#include "init_error.hpp"
#include "sdl_renderer.hpp"
#include "texture.hpp"

namespace sdl {
    SDL_Renderer* makeRenderer(SDL_Window* win);

    SDLRenderer::SDLRenderer(SDL_Window* win, int w,
                             int h) noexcept(false)
        : w(w), h(h), renderer(makeRenderer(win)),
          pixels(new Uint32[w * h]), texture(renderer, w, h) {
	if (renderer == NULL) {
	    std::stringstream ss;
	    ss << "SDL_CreateRenderer failed: " << SDL_GetError();
	    throw err::InitError(ss);
	}

	memset(pixels, 0, w * h * sizeof(Uint32));
    }

    SDL_Renderer* makeRenderer(SDL_Window* win) noexcept(false) {
	auto renderer = SDL_CreateRenderer(win, -1,
	                                   SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
	    // Necessary because the caller can't check success yet.
	    // Bad code, but deprecated.
	    std::stringstream ss;
	    ss << "SDL_CreateRenderer failed: " << SDL_GetError();
	    throw err::InitError(ss);
	}

	return renderer;
    }

    void SDLRenderer::drawPoint(int x, int y, int color) {
	pixels[y * w + x] = color;
    }

    void SDLRenderer::update() {
	texture.update(NULL, pixels, w * sizeof(Uint32));
    }

    void SDLRenderer::draw() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture.handle(), NULL, NULL);
	SDL_RenderPresent(renderer);
    }

    void SDLRenderer::clear() {
	memset(pixels, 0, w * h * sizeof(Uint32));
    }

    SDLRenderer::~SDLRenderer() {
	SDL_DestroyRenderer(renderer);
	delete[] pixels;
    }
} // namespace sdl
