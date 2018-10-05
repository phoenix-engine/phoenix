#include <iostream>
#include <sstream>

#include "phoenix.hpp"

#include "gl_renderer.hpp"
#include "graphics.hpp"
#include "sdl_renderer.hpp"

namespace phx {

    template <class R>
    Phoenix<R>::Phoenix(const std::string& title) noexcept(false)
        : sdlUtil(title, R::windowFlags(), R::sdlDefaults(),
                  &R::postHooks),
          gfxh(sdlUtil.windowHandle(), sdlUtil.w(), sdlUtil.h()) {}

    template <class R>
    void Phoenix<R>::render() noexcept(false) {
	gfxh.clear();
	gfxh.update();
	gfxh.draw();
    }

    template class Phoenix<sdl::GLRenderer>;
    template class Phoenix<sdl::SDLRenderer>;

}; // namespace phx
