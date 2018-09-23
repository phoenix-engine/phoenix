#ifndef PHX_SDL_RENDERER
#define PHX_SDL_RENDERER

#include "SDL.h"

namespace sdl {

    /**
     * Renderer is an interface for renderer implementations; that is,
     * it specifies an API which Phoenix uses to visualize entities.
     *
     * The intent of the Renderer is not to be used with dynamic
     * implementations, but rather to specify the API expected for
     * renderers.  The Phoenix class is explicitly templated with
     * sdl::GLRenderer and sdl::SDLRenderer.
     *
     * A later implementation will allow Renderer subclasses to be used
     * as the Phoenix Renderer.
     */
    class Renderer {
    public:
	Renderer(SDL_Window*, int w, int h) noexcept(false);

	virtual void update();
	virtual void draw();
	virtual void clear();

	virtual void drawPoint(int x, int y, int color);
    };
} // namespace sdl

#endif
