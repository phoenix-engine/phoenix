#ifndef PHX_PHOENIX_H
#define PHX_PHOENIX_H

#include "graphics.hpp"
#include "sdl_util.hpp"

namespace phx {

    template <class R>
    class Phoenix {
    public:
	Phoenix(const std::string& title) noexcept(false);

    private:
	sdl::SDLUtil     sdlUtil;
	gfx::Graphics<R> gfx;
    };

}; // namespace phx

#endif
