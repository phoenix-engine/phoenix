#ifndef PHX_PHOENIX_H
#define PHX_PHOENIX_H

#include "graphics.hpp"
#include "input.hpp"

#include "event.hpp"
#include "queue.hpp"

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
    template <typename Consumer, typename Renderer,
              typename RenderPayload = std::nullptr_t>
    class Phoenix {
	using GP = gfx::Graphics<Renderer, RenderPayload>;

    public:
	// Phoenix is intended to own and manage the memory of all of
	// its internal components, so it needs to be default-
	// constructible on certain platforms where the object
	// containing it might be allocated ahead of time.
	Phoenix() = default;

	// This is the correct way to initialize a new usable Phoenix
	// object.  Note that its handles are moved out of the calling
	// context, so if they need to be used by reference elsewhere,
	// references should be taken using the "input_handle" etc.
	// methods.
	Phoenix(GP&& g, input::Input<Consumer>&& in) noexcept(true);

	// Only move, never copy, a Phoenix object.
	inline Phoenix& operator=(Phoenix&&) = default;

	void render(RenderPayload) noexcept(false);
	// void enqueue(event::Event&&) noexcept(true);

	input::Input<Consumer>& input_handle() noexcept(true);

    private:
	GP                     gf;
	input::Input<Consumer> in;
    };

#include "impl/phoenix_impl.hxx"

}; // namespace phx

#endif
