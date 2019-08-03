#ifndef PHX_SDL_VK_RENDERER
#define PHX_SDL_VK_RENDERER

#include <memory>
#include <type_traits>

#include <SDL.h>

#include <vulkan/vulkan.hpp>

#include "prelude.hpp"

#include "phx_sdl/window.hpp"

namespace phx_sdl {

    template <bool debugging>
    class VKRenderer;

    namespace cleanup {
	template <bool debugging>
	void destroy_vk(VKRenderer<debugging>*);

	template <bool debugging>
	struct VKDestroyer
	    : public std::unique_ptr<VKRenderer<debugging>,
	                             decltype(&destroy_vk<debugging>)> {
	    VKDestroyer(VKRenderer<debugging>*);
	};
    } // namespace cleanup

    template <bool debugging = false>
    class VKRenderer {
    public:
	VKRenderer(const Window&);
	VKRenderer(VKRenderer&&) noexcept;

	static const Uint32 window_flags() noexcept;
	static void         post_hooks() noexcept;
	gfx::extent         extent() noexcept;

	void clear();
	void update();
	void draw(std::nullptr_t);

    private:
	// SDL Window handle.
	const Window& window;

	// Vulkan instance handle.
	vk::Instance instance;

	// Vulkan physical and virtual device handles.
	vk::PhysicalDevice phys_device;
	vk::Device         device;

	// Vulkan graphics and presentation queues.
	vk::Queue grph_queue;
	vk::Queue pres_queue;

	// Vulkan native components.
	vk::SurfaceKHR     surface;
	vk::PipelineCache  pl_cache;
	vk::Pipeline       pipeline;
	vk::PipelineLayout pl_layout;

	// Swapchain components.
	vk::SwapchainKHR             swapchain;
	vk::SurfaceFormatKHR         swc_format;
	vk::Extent2D                 swc_extent;
	std::vector<vk::Image>       swc_images;
	std::vector<vk::ImageView>   swc_image_views;
	std::vector<vk::Framebuffer> swc_framebuffers;

	// Rendering components.
	vk::RenderPass                 render_pass;
	vk::CommandPool                cmd_pool;
	std::vector<vk::CommandBuffer> cmd_buffers;

	// Synchronization components.
	static const int max_frames_inflight = 2;

	size_t current_frame;

	// img_ready is signaled when the swapchain image has been
	// acquired during the draw call.
	std::array<vk::Semaphore, max_frames_inflight> img_ready;

	// render_done is signaled when the swapchain image has been
	// presented.
	std::array<vk::Semaphore, max_frames_inflight> render_done;

	std::array<vk::Fence, max_frames_inflight> inflight_fences;

	// Rendering metrics.
	std::chrono::high_resolution_clock::time_point last_frame_time;
	uint64_t                                       frame_count;

	// Resources that need dynamic lifetime and constant address.
	std::unique_ptr<float>               queue_priority;
	std::unique_ptr<vk::ApplicationInfo> app_info;

	// TODO: Refactor into a usable debugger harness or API, e.g.
	// with auto extension config + dynamic loader built-in exposing
	// required APIs.

	// Debugging helper.
	std::conditional_t<debugging, vk::DebugUtilsMessengerEXT,
	                   std::nullptr_t>
	  debug_messenger;

	// Vulkan dynamic dispatch / loader.
	vk::DispatchLoaderDynamic dyn_loader;

	int width;
	int height;

	// Cleanup needs the ability to call teardown for this.
	friend void cleanup::destroy_vk<debugging>(VKRenderer*);

	// SDL window creation flags for debugging only.
	static const Uint32 debug_window_flags() noexcept;

	// If the swapchain is no longer valid (eErrorOutOfDateKHR),
	// call this to reload it.  Then throw phx_err::Retry to ditch
	// transient state and retry the draw.
	void reload_swapchain();

	// Finalizer to be called by destroyer at the final end-of-life
	// of the VKRenderer (after all moves, etc.)
	void teardown();

	// Lifetime management helper.
	//
	// Note that this must be the last member variable declared in
	// the class, since teardown must be called before the
	// end-of-life of the other member variables.
	//
	// According to the spec, the destructors of class members are
	// called "in reverse order of declaration" (last declared is
	// first called.)  Therefore, the destroyer will call its
	// deleter (teardown) before the destructors of any other
	// member, as long as it is declared last.
	cleanup::VKDestroyer<debugging> destroyer;
    };

} // namespace phx_sdl

#endif // PHX_SDL_VK_RENDERER