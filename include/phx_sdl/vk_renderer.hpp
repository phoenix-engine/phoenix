#ifndef PHX_SDL_VK_RENDERER
#define PHX_SDL_VK_RENDERER

#include <chrono>
#include <memory>
#include <type_traits>

#include "lifetime.hpp"
#include "phx_sdl/scene.hpp"
#include "phx_sdl/window.hpp"
#include "prelude.hpp"

#include <SDL.h>
#include <glm/vec2.hpp>

#include <vulkan/vulkan.hpp>

namespace phx_sdl {

    template <bool debugging>
    class VKRenderer;

    namespace cleanup {

	template <bool debugging>
	void destroy_vk(VKRenderer<debugging>*);

	template <bool debugging>
	using VKKeeper = phx::ResourceKeeper<VKRenderer<debugging>,
	                                     destroy_vk<debugging>>;

    } // namespace cleanup

    // Functionality for bridging GLSL / C++.
    namespace bridge {

	// The interface to user intentions.
	struct Intent {
	    // The direction the user indicates.
	    glm::vec2 m;
	};

	struct Aspect {
	    // The ratio of screen width to screen height.
	    float a;
	};

	struct PushConstants {
	    // A container for all push constants.
	    Intent i;
	    Aspect a;
	};

	static_assert(sizeof(PushConstants) <= 128);

    }; // namespace bridge

    struct TransientCommand {
	vk::CommandBuffer buf;
	vk::Event         evt;

	enum struct status { ready, pending, signaled };
	status stat;
	// update_status queries the status of the event on the device
	// and updates it internally.
	status update_status(const vk::Device&);
    };

    template <bool debugging = false>
    class VKRenderer {
    public:
	// Default and copy constructors disabled.
	VKRenderer()            = delete;
	VKRenderer(VKRenderer&) = delete;

	VKRenderer(Window&&, const Scene& = DefaultScenes::triangle);
	VKRenderer(VKRenderer&&) noexcept;

	static const Uint32 window_flags() noexcept;
	static void         post_hooks() noexcept;
	gfx::extent         extent() noexcept;

	void clear();
	void update(const event::EventIntent&);
	void draw(std::nullptr_t);

	struct Metrics {
	    using clock = std::chrono::high_resolution_clock;
	    static_assert(clock::is_steady,
	                  "High-resolution clock is not steady!");
	    using time   = clock::time_point;
	    using dur    = clock::duration;
	    using rep    = clock::rep;
	    using period = clock::period;
	    using ms     = std::chrono::duration<double, std::milli>;

	    dur avg_frame_time;
	    dur max_frame_time;
	};

	Metrics get_metrics() noexcept;

    private:
	// SDL Window handle.
	Window window;

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

	// Descriptor sets, uniform buffers, memory, etc.
	vk::DescriptorSetLayout descriptor_set_layout;

	/* We don't use UBO's yet.
	std::vector<vk::Buffer>       buffers;
	std::vector<vk::DeviceMemory> buffer_memory;
	*/

	// Rendering components.
	vk::RenderPass                 render_pass;
	vk::CommandPool                cmd_pool;
	vk::CommandPool                tmp_cmd_pool;
	std::vector<vk::CommandBuffer> cmd_buffers;

	std::deque<TransientCommand> tmp_cmds;

	// Synchronization components.
	static const int max_frames_inflight = 2;

	size_t current_frame;

	// Metrics stuff.
	inline static const double alpha = 0.8;

	Metrics                metrics;
	typename Metrics::time prev_frame_time;

	// img_ready is signaled when the swapchain image has been
	// acquired during the draw call.
	std::array<vk::Semaphore, max_frames_inflight> img_ready;

	// render_done is signaled when the swapchain image has been
	// presented.
	std::array<vk::Semaphore, max_frames_inflight> render_done;

	std::array<vk::Fence, max_frames_inflight> inflight_fences;

	// Resources that need dynamic lifetime and constant address.
	std::unique_ptr<float>               queue_priority;
	std::unique_ptr<vk::ApplicationInfo> app_info;

	// Resources that exist outside of the lifetime of the Renderer.
	const Scene& scene;

	// State and push constants.
	bridge::Intent intent;

	// TODO: Refactor into a usable debugger harness or API, e.g.
	// with auto extension config + dynamic loader built-in
	// exposing required APIs.

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

	cleanup::VKKeeper<debugging> destroyer;
    };

} // namespace phx_sdl

#endif // PHX_SDL_VK_RENDERER
