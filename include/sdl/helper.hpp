#ifndef PHX_SDL_HELPER
#define PHX_SDL_HELPER

#include "SDL.h"

namespace sdl {
    // Helper is a wrapper "namespace" for configuration, utilities,
    // etc. related to SDL and OpenGL.
    class Helper {
    public:
	// This class is never meant to be constructed.
	Helper()  = delete;
	~Helper() = delete;

	// Preconfigured post-hooks.  Users may add to these in their
	// own implementations.  See gl_renderer/gl_renderer.cxx for an
	// example.
	static void noop() noexcept(true) {}
	static void glPostHooks() noexcept(false);
	static void sdlOnlyPostHooks() noexcept(false);

	// SDL / OpenGL-related utilities for use by Graphics, Renderer,
	// etc.
	static void setSDLGLAttr(const SDL_GLattr,
	                         const int) noexcept(false);
	static void setSDLGLAttr(const SDL_GLattr, const int,
	                         const std::string&) noexcept(false);
	static int  getGLAttr(const SDL_GLattr what) noexcept(false);
    };
} // namespace sdl
#endif
