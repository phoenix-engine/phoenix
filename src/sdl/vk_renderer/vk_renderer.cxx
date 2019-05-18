#include <vector>

#include <SDL.h>
#include <SDL_vulkan.h>

#include <vulkan/vulkan.hpp>

#include "phx_sdl/vk_renderer.hpp"
#include "phx_sdl/window.hpp"
#include "sdl_init_error.hpp"

namespace phx_sdl {

    const Uint32 VKRenderer::window_flags() noexcept {
	return SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN |
	       SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_VULKAN |
	       SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_INPUT_FOCUS |
	       SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS;
    }

    const Uint32 VKRenderer::debug_window_flags() noexcept {
	return SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI |
	       SDL_WINDOW_VULKAN;
    }

    VKRenderer::VKRenderer(const Window& w) {
	auto whandle = w.handle();
	auto get_ex  = SDL_Vulkan_GetInstanceExtensions;

	uint32_t num_extns;

	if (auto ok = get_ex(whandle, &num_extns, nullptr); !ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_GetInstanceExtensions failed (get count)");
	}

	std::vector<const char*> extns(num_extns);
	if (auto ok = get_ex(whandle, &num_extns, extns.data()); !ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_GetInstanceExtensions failed (get data)");
	}

	std::vector<const char*> layers;

	// uncomment below if you want to use validation layers
	layers.push_back("VK_LAYER_LUNARG_standard_validation");

	auto app_info = vk::ApplicationInfo(w.get_title(), 0,
	                                    "Phoenix Engine", 0, 0);

	auto size_layers = static_cast<uint32_t>(layers.size());
	auto size_extns  = static_cast<uint32_t>(extns.size());

	auto with_info = vk::InstanceCreateInfo(
	  vk::InstanceCreateFlags(), &app_info, size_layers,
	  layers.data(), size_extns, extns.data());

	// create the Vulkan instance
	auto inst   = vk::Instance();
	auto result = vk::createInstance(&with_info, NULL, &inst);
	if (result != vk::Result::eSuccess) {
	    std::stringstream ss;
	    ss << "vk::createInstance failed with " << result;
	    throw phx_err::InitError(ss);
	}

	VkSurfaceKHR vksfc;
	auto ok = SDL_Vulkan_CreateSurface(whandle, inst, &vksfc);
	if (!ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_CreateSurface failed");
	}

	surface = vk::SurfaceKHR(vksfc);
    }

    void VKRenderer::update() {}
    void VKRenderer::draw(std::nullptr_t) {}
    void VKRenderer::clear() {}

} // namespace phx_sdl