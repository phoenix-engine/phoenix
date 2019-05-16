#ifndef PHX_SDL_VK_RENDERER
#define PHX_SDL_VK_RENDERER

#include <SDL.h>

#include <vulkan/vulkan.hpp>

#include "phx_sdl/window.hpp"

namespace phx_sdl {

    class VKRenderer {
    public:
	VKRenderer(const Window&);

	static const Uint32 window_flags() noexcept;
	static const Uint32 debug_window_flags() noexcept;

	void clear();
	void update();
	void draw(std::nullptr_t);

    private:
	vk::SurfaceKHR surface;
    };

} // namespace phx_sdl

#endif // PHX_SDL_VK_RENDERER