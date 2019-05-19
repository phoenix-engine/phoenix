#ifndef PHX_SDL_HELPER
#define PHX_SDL_HELPER

#include "SDL.h"

namespace phx_sdl {

    // Helper is a wrapper "namespace" for configuration, utilities,
    // etc. related to SDL and OpenGL.
    class Helper {
    public:
	// This class is never meant to be constructed.
	Helper()  = delete;
	~Helper() = delete;

	// Preconfigured post-hooks.  Users may add to these in their
	// own implementations.
	static void noop() noexcept(true) {}
	static void sdlOnlyPostHooks() noexcept(false);

    };

} // namespace phx_sdl
#endif
