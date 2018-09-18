#include <iostream>
#include <sstream>

#include "gl_renderer.hpp"
#include "graphics.hpp"
#include "init_error.hpp"
#include "phoenix.hpp"
#include "renderer.hpp"

namespace phx {

    template <class G>
    Phoenix<G>::Phoenix(const std::string& title) noexcept(false)
        : sdlUtil(title,
                  SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI |
                    SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED),
          gfx(sdlUtil.windowHandle(), sdlUtil.w(), sdlUtil.h()) {}

    template class Phoenix<sdl::GLRenderer>;
    template class Phoenix<sdl::Renderer>;

}; // namespace phx
