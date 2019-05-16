#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "phx_sdl/texture.hpp"

namespace phx_sdl {

    Texture::Texture(SDL_Renderer* renderer, int w,
                     int h) noexcept(false) {
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                            SDL_TEXTUREACCESS_STREAMING, w, h);
	if (texture == NULL) {
	    std::stringstream ss;
	    ss << "SDL_CreateTexture failed: " << SDL_GetError();
	    throw phx_err::InitError(ss);
	}
    }

    void Texture::update(const SDL_Rect* rect, const Uint32* pixels,
                         int pitch) noexcept(false) {
	if (int v = SDL_UpdateTexture(texture, rect, pixels, pitch) !=
	            0) {
	    std::stringstream ss;
	    ss << "SD_UpdateTexture failed with " << v << ": "
	       << SDL_GetError();
	    throw phx_err::InitError(ss);
	}
    }

    Texture::~Texture() { SDL_DestroyTexture(texture); }

}; // namespace phx_sdl
