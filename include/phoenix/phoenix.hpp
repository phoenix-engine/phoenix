#ifndef PHX_PHOENIX_H
#define PHX_PHOENIX_H

#include "graphics.hpp"
#include "sdl_util.hpp"

namespace phx {

    /** Phoenix contains, manages lifecycles for, and offers APIs to
     * manipulate engine components for graphics, audio, physics, game
     * state, and more.  To access internal components directly, use the
     * Handle* methods.  This is recommended only for advanced or custom
     * usage.
     *
     * Phoenix is templated with a Renderer for its Graphics module.  To
     * allow third-party Renderers, a virtual Renderer class is defined
     * in include/sdl/renderer.hpp.  The current implementation requires
     * the templated Phoenix class for the Renderer to be declared in
     * src/phoenix/phoenix.cxx.  A similar pattern is followed for its
     * other modules.
     */
    template <class R>
    class Phoenix {
    public:
	Phoenix(const std::string& title) noexcept(false);

	void render() noexcept(false);

    private:
	sdl::SDLUtil     sdlUtil;
	gfx::Graphics<R> gfxh;
    };

}; // namespace phx

#endif
