#include <cstddef>
#include <cstring>
#include <sstream>

#include "SDL.h"

#include "phx_sdl/helper.hpp"
#include "phx_sdl/sdl_renderer.hpp"
#include "phx_sdl/texture.hpp"
#include "sdl_init_error.hpp"

namespace phx_sdl {

    SDL_Renderer* makeRenderer(SDL_Window* win);

    const Uint32 SDLRenderer::windowFlags() noexcept(true) {
	return SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN |
	       SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_GRABBED |
	       SDL_WINDOW_INPUT_GRABBED;
    }

    const Uint32 SDLRenderer::sdlDefaults() noexcept(true) {
	return SDL_INIT_AUDIO | SDL_INIT_VIDEO;
    }

    void SDLRenderer::postHooks() noexcept(true) {
	Helper::sdlOnlyPostHooks();
    }

    SDLRenderer::SDLRenderer(SDL_Window* win, int w,
                             int h) noexcept(false)
        : w(w), h(h), renderer(makeRenderer(win)),
          pixels(new Uint32[w * h]), texture(renderer, w, h) {
	clear();
    }

    SDL_Renderer* makeRenderer(SDL_Window* win) noexcept(false) {
	auto renderer = SDL_CreateRenderer(win, -1,
	                                   SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
	    // Necessary because the caller can't check success yet.
	    // Bad code, but deprecated.
	    throw phx_err::SDLInitError("SDL_CreateRenderer failed");
	}

	return renderer;
    }

    void SDLRenderer::drawPoint(int x, int y, int color) {
	pixels[y * w + x] = color;
    }

    void SDLRenderer::update() {
	texture.update(nullptr, pixels, w * sizeof(Uint32));
    }

    void SDLRenderer::draw() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture.handle(), nullptr, nullptr);
	SDL_RenderPresent(renderer);
    }

    void SDLRenderer::clear() {
	std::memset(pixels, 0, w * h * sizeof(Uint32));
    }

    SDLRenderer::~SDLRenderer() {
	SDL_DestroyRenderer(renderer);
	delete[] pixels;
    }

} // namespace phx_sdl
