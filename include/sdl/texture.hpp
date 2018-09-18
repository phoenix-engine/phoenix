#ifndef PHX_SDLTEXTURE_H
#define PHX_SDLTEXTURE_H

#include "SDL.h"

namespace sdl {
    class Texture {
    public:
	Texture(SDL_Renderer* renderer, int w = 640,
	        int h = 480) noexcept(false);
	~Texture();

	void update(const SDL_Rect*, const Uint32*,
	            int) noexcept(false);

	SDL_Texture* handle() { return texture; }

    private:
	SDL_Texture* texture;
    };
} // namespace sdl

#endif
