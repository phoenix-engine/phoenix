#ifndef PHX_PHOENIX_H
#define PHX_PHOENIX_H

#include "graphics.hpp"

namespace phx {

    /** Phoenix contains, manages lifecycles for, and offers APIs to
     * manipulate engine components for graphics, audio, physics, game
     * state, and more.
     *
     * Phoenix is templated with a Renderer for its Graphics module.  To
     * allow third-party Renderers, a virtual Renderer class is defined
     * in include/sdl/renderer.hpp.  A similar pattern is followed for
     * its other modules.
     */
    template <typename R>
    class Phoenix {
    public:
	Phoenix(gfx::Graphics<R>&& g) noexcept(true);

	Phoenix()          = delete;
	Phoenix(Phoenix&)  = delete;
	Phoenix(Phoenix&&) = delete;

	void render() noexcept(false);

    private:
	gfx::Graphics<R> gfxh;
    };

#include "phoenix.hxx"
}; // namespace phx

#endif
