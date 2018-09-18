#include <iostream>
#include <sstream>

#include "SDL.h"

#include "init_error.hpp"
#include "init_util.hpp"

namespace sdl {
    InitUtil::InitUtil(Uint32 flags) noexcept(false) {
	if (int initOk = SDL_Init(flags) != 0) {
	    std::stringstream ss;
	    ss << "SDL_Init failed with code " << initOk << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}

	if (int glOk = SDL_GL_LoadLibrary(NULL) != 0) {
	    std::stringstream ss;
	    ss << "SDL_GL_LoadLibrary failed with code " << glOk << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}

	// Request an OpenGL 4.1 context (should be core)
	if (int visOk = SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
	                                    1) != 0) {
	    std::stringstream ss;
	    ss << "SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1) "
	       << "failed with code " << visOk << ": "
	       << SDL_GetError();
	    throw err::InitError(ss);
	}

	if (int ctxMajOk = SDL_GL_SetAttribute(
	                     SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0) {
	    std::stringstream ss;
	    ss
	      << "SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) "
	      << "failed with code " << ctxMajOk << ": "
	      << SDL_GetError();
	    throw err::InitError(ss);
	}

	if (int minOk = SDL_GL_SetAttribute(
	                  SDL_GL_CONTEXT_MINOR_VERSION, 1) != 0) {
	    std::stringstream ss;
	    ss
	      << "SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) "
	      << "failed with code " << minOk << ": " << SDL_GetError();
	    throw err::InitError(ss);
	}

	// // Also request a depth buffer
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    }

    InitUtil::~InitUtil() { SDL_Quit(); }
}; // namespace sdl
