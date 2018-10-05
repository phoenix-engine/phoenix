#ifndef PHX_SDL_INITUTIL_H
#define PHX_SDL_INITUTIL_H

namespace sdl {
    // InitUtil simply handles SDL_Init and SDL_Quit.
    class InitUtil {
    public:
	InitUtil(Uint32 flags) noexcept(false);
	~InitUtil();
    };
} // namespace sdl

#endif
