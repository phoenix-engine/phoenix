#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "errors.hpp"
#include "phx_sdl/vk_renderer.hpp"
#include "phx_sdl/window.hpp"
#include "sdl_init_error.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include <vulkan/vulkan.hpp>

// #include <Eigen/Dense>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <id.hpp>
#include <mapper.hpp>
#include <resource.hpp>

namespace phx_sdl {

    namespace cleanup {

	template <bool debugging>
	void destroy_vk(VKRenderer<debugging>* r) {
	    r->teardown();
	}

    } // namespace cleanup

    // This anonymous namespace contains mostly Vulkan-related loaders,
    // constants, etc.
    namespace {

	// TODO: Define "debug mode" interfaces -- consider logging
	// errors to MSVC in MSVC builds.
	VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_utils_log_message(
	  VkDebugUtilsMessageSeverityFlagBitsEXT      severity,
	  VkDebugUtilsMessageTypeFlagsEXT             type_flags,
	  const VkDebugUtilsMessengerCallbackDataEXT* data,
	  void*                                       user_data) {

	    // TODO: Use a custom class / singleton / something for
	    // logging.
	    std::cerr << "validation layer ["
	              << vk::to_string(
	                   static_cast<
	                     vk::DebugUtilsMessageSeverityFlagBitsEXT>(
	                     severity))
	              << "]: " << data->pMessage << std::endl;
	    return VK_FALSE;
	}

	// TODO: Make these into parameters of the Renderer config.
	const vk::DebugUtilsMessageSeverityFlagsEXT
	  debug_utils_severity =
	    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
	    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
	    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;

	const vk::DebugUtilsMessageTypeFlagsEXT debug_utils_msgtype =
	  vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
	  vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
	  vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;

	const std::set<std::string> required_inst_extns{
	    VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME,
	    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
	    VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME,
	};

	const std::set<std::string> required_dev_extns{
	    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	    VK_KHR_MAINTENANCE2_EXTENSION_NAME,
	    VK_KHR_MULTIVIEW_EXTENSION_NAME,
	    VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME,
	    VK_KHR_DEVICE_GROUP_EXTENSION_NAME,
	};

	// Vulkan device mask will be assumed constant here.
	// TODO: Multi-device?
	// https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#devsandqueues-devices
	const uint32_t DEVICE_MASK = 0x00000001;

	template <typename ST>
	void render_available_extns(ST& estr) {
	    auto extn_props =
	      vk::enumerateInstanceExtensionProperties();
	    estr << "Found " << extn_props.size()
	         << " available instance extensions:" << std::endl;

	    size_t maxw = 0;
	    for (const auto& p : extn_props) {
		if (auto ew = strlen(p.extensionName); maxw < ew) {
		    maxw = ew;
		}
	    }

	    std::sort(extn_props.begin(), extn_props.end(),
	              [&](const auto& p1, const auto& p2) {
		          return strcmp(p1.extensionName,
		                        p2.extensionName) < 0;
	              });

	    for (const auto& e : extn_props) {
		estr << "  " << std::setw(maxw) << std::left
		     << e.extensionName << " | "
		     << "spec version: " << e.specVersion << std::endl;
	    }

	    estr << std::endl;
	}

	struct device_info {
	    uint16_t                                rank;
	    vk::PhysicalDeviceFeatures              feats;
	    vk::PhysicalDeviceProperties            props;
	    std::vector<vk::QueueFamilyProperties2> qfam_props;
	    std::vector<vk::ExtensionProperties>    extn_props;
	};

	struct queue_info {
	    std::set<uint32_t> graphics_indices;
	    std::set<uint32_t> compute_indices;
	    std::set<uint32_t> presentation_indices;
	};

	struct swapchain_info {
	    vk::SurfaceCapabilities2KHR        sfc_capabilities;
	    std::vector<vk::SurfaceFormat2KHR> sfc_formats;
	    std::vector<vk::PresentModeKHR>    present_modes;
	};

	swapchain_info
	get_swapchain_info(const vk::PhysicalDevice&        device,
	                   const vk::SurfaceKHR&            surface,
	                   const vk::DispatchLoaderDynamic& loader) {

	    vk::PhysicalDeviceSurfaceInfo2KHR info(surface);

	    swapchain_info result{
		device.getSurfaceCapabilities2KHR(info, loader),
		device.getSurfaceFormats2KHR(info, loader),
		device.getSurfacePresentModesKHR(surface),
	    };

	    return result;
	}

	vk::SurfaceFormatKHR select_format(
	  const std::vector<vk::SurfaceFormat2KHR>& available_formats) {

	    // Short-circuit format picking if format is "undefined"
	    // (user selected.)
	    if (available_formats.size() == 1 &&
	        available_formats[0].surfaceFormat.format ==
	          vk::Format::eUndefined) {
		return vk::SurfaceFormatKHR{
		    vk::Format::eB8G8R8A8Unorm,
		    vk::ColorSpaceKHR::eSrgbNonlinear,
		};
	    }

	    for (const auto& sfc_format : available_formats) {
		if (sfc_format.surfaceFormat.format ==
		      vk::Format::eB8G8R8A8Unorm &&
		    sfc_format.surfaceFormat.colorSpace ==
		      vk::ColorSpaceKHR::eSrgbNonlinear) {

		    return sfc_format.surfaceFormat;
		}
	    }

	    return available_formats[0].surfaceFormat;
	}

	vk::PresentModeKHR select_present_mode(
	  const std::vector<vk::PresentModeKHR>& available_modes) {

	    for (const auto& mode : available_modes) {
		if (mode == vk::PresentModeKHR::eMailbox) {
		    return mode;
		}
	    }

	    return vk::PresentModeKHR::eFifo;
	}

	vk::Extent2D select_swap_extent(
	  const vk::SurfaceCapabilities2KHR& capabilities,
	  uint32_t width, uint32_t height) {

	    const auto& sfc_cap = capabilities.surfaceCapabilities;

	    // If the current extent is configurable, its value is set
	    // to the maximum value of uint32_t.  If it's not, simply
	    // select the given extent.
	    if (sfc_cap.currentExtent.width !=
	        std::numeric_limits<uint32_t>::max()) {
		return sfc_cap.currentExtent;
	    }

	    // If it is configurable, select width and height by the
	    // greater of the minimum extent defined by the capability,
	    // or the window size, bounded by the maximum extent defined
	    // by the capability.
	    //
	    // I.e., select the renderer's extent size as the window
	    // size, bounded by the greatest and least size defined by
	    // its surface capabilities.
	    const auto& max_width = std::min(
	      sfc_cap.maxImageExtent.width, width);
	    const auto& max_height = std::min(
	      sfc_cap.maxImageExtent.height, height);

	    return vk::Extent2D{
		std::max(sfc_cap.minImageExtent.width, max_width),
		std::max(sfc_cap.minImageExtent.height, max_height),
	    };
	}

	uint16_t
	rank_physical_device(const vk::PhysicalDevice&        device,
	                     const vk::SurfaceKHR&            surface,
	                     const vk::DispatchLoaderDynamic& loader) {

	    // TODO: Grok properties.pNext dynamic extension info
	    // stuff.

	    // TODO: Check for required extensions.
	    // vk::EnumerateDeviceExtensionProperties
	    const auto& feat  = device.getFeatures2().features;
	    const auto& props = device.getProperties2().properties;
	    const auto& qfams = device.getQueueFamilyProperties2();
	    const auto& extns =
	      device.enumerateDeviceExtensionProperties();
	    const auto& swapchain_info = get_swapchain_info(
	      device, surface, loader);

	    uint16_t rank = 0;

	    std::set<std::string> missing_required_extns{};

	    std::copy(required_dev_extns.begin(),
	              required_dev_extns.end(),
	              std::inserter(missing_required_extns,
	                            missing_required_extns.begin()));

	    // Check whether each required extension is present.
	    for (const auto& extn : extns) {
		missing_required_extns.erase(extn.extensionName);
	    }

	    // Can't proceed with missing extensions.
	    if (missing_required_extns.size() > 0) {
		return 0;
	    }

	    // Can't proceed with insufficient swapchain.
	    if (swapchain_info.present_modes.empty() ||
	        swapchain_info.sfc_formats.empty()) {
		return 0;
	    }

	    // Only use dedicated and integrated devices.
	    switch (props.deviceType) {
	    case vk::PhysicalDeviceType::eDiscreteGpu:
		rank = 200;
		break;
	    case vk::PhysicalDeviceType::eIntegratedGpu:
		rank = 50;
		break;
	    default:
		return 0;
	    }

	    if (feat.geometryShader) {
		rank += 10;
	    }

	    // TODO: Check for compute stuff?
	    // if (props.limits.compute...)

	    // Look for a queue family which supports at least
	    // graphics.
	    bool acceptable_queue_families = false;
	    for (const auto& fam : qfams) {
		auto flags = fam.queueFamilyProperties.queueFlags;
		if (flags & vk::QueueFlagBits::eGraphics) {
		    acceptable_queue_families = true;
		    break;
		}
	    }

	    if (!acceptable_queue_families) {
		return 0;
	    }

	    // TODO: If compute is mandatory, check here.
	    // If it supports compute, even better.
	    for (const auto& fam : qfams) {
		auto flags = fam.queueFamilyProperties.queueFlags;
		if (flags & vk::QueueFlagBits::eCompute) {
		    rank += 50;
		}
	    }

	    return rank;
	}

	template <typename ST>
	void render_available_devices(
	  ST& estr, const std::vector<vk::PhysicalDevice>& devices,
	  const vk::SurfaceKHR&            surface,
	  const vk::DispatchLoaderDynamic& loader) {

	    estr << "Physical graphics devices:" << std::endl;

	    size_t maxw = 0;

	    std::vector<device_info> info;

	    // Insert the device metadata into the info vector.
	    for (auto i = 0; i < devices.size(); i++) {
		const auto& dev = devices[i];

		auto extn_props =
		  dev.enumerateDeviceExtensionProperties();

		std::sort(extn_props.begin(), extn_props.end(),
		          [&](const auto& str1, const auto& str2) {
		              return (strcmp(str1.extensionName,
		                             str2.extensionName) < 0);
		          });

		info.emplace_back(device_info{
		  rank_physical_device(dev, surface, loader),
		  dev.getFeatures2().features,
		  dev.getProperties2().properties,
		  dev.getQueueFamilyProperties2(),
		  extn_props,
		});
	    }

	    // Find the largest name to set the column width later.
	    for (const auto& i : info) {
		if (auto nw = strlen(i.props.deviceName); maxw < nw) {
		    maxw = nw;
		}
	    }

	    // Sort the info list alphabetically by device name.
	    std::sort(info.begin(), info.end(),
	              [&](const auto& i1, const auto& i2) {
		          return (strcmp(i1.props.deviceName,
		                         i2.props.deviceName) < 0);
	              });

	    // Render the list.
	    // TODO: Render more properties.
	    for (const auto& i : info) {
		estr << "  " << std::setw(maxw) << std::left
		     << i.props.deviceName << " | (rank " << i.rank
		     << ") " << vk::to_string(i.props.deviceType)
		     << std::endl;
	    }

	    for (const auto& i : info) {
		estr << std::endl
		     << "Supported extensions (" << i.props.deviceName
		     << "): " << std::endl;

		for (const auto& ep : i.extn_props) {
		    estr << "  " << ep.extensionName << std::endl;
		}

		estr << std::endl;
	    }

	    estr << std::endl;
	}

	template <bool debugging,
	          typename Ordering = std::greater<uint16_t>>
	std::multimap<uint16_t, int, Ordering>
	get_ranks(const std::vector<vk::PhysicalDevice>& devices,
	          const vk::SurfaceKHR&                  surface,
	          const vk::DispatchLoaderDynamic&       loader) {

	    // Note multimap is sorted according to rank (greatest
	    // to least.)
	    std::multimap<uint16_t, int, Ordering> ranked{};
	    if constexpr (debugging) {
		std::cerr << std::endl;
		render_available_devices(std::cerr, devices, surface,
		                         loader);
	    }

	    // Match ranks to device indices.
	    for (int i = 0; i < devices.size(); i++) {
		ranked.insert(std::make_pair(
		  rank_physical_device(devices[i], surface, loader),
		  i));
	    }

	    return ranked;
	}

	queue_info get_queue_info(const vk::PhysicalDevice& device,
	                          const vk::SurfaceKHR&     surface) {

	    queue_info result{
		std::set<uint32_t>{},
		std::set<uint32_t>{},
		std::set<uint32_t>{},
	    };

	    const auto& props = device.getQueueFamilyProperties2();
	    for (auto i = 0; i < props.size(); i++) {
		const auto& p     = props[i];
		const auto& flags = p.queueFamilyProperties.queueFlags;
		const auto& sfc_support = device.getSurfaceSupportKHR(
		  i, surface);

		if (flags & vk::QueueFlagBits::eGraphics) {
		    result.graphics_indices.insert(i);
		}
		if (flags & vk::QueueFlagBits::eCompute) {
		    result.compute_indices.insert(i);
		}
		if (sfc_support) {
		    result.presentation_indices.insert(i);
		}
	    }

	    return result;
	}

	std::tuple<vk::SwapchainKHR, vk::SurfaceFormatKHR, vk::Extent2D>
	create_swapchain(
	  const vk::PhysicalDevice& phys_device,
	  const vk::Device& device, const vk::SurfaceKHR& surface,
	  const vk::DispatchLoaderDynamic& loader, uint32_t width,
	  uint32_t height,
	  std::optional<std::reference_wrapper<vk::SwapchainKHR>>
	    old_swapchain = {}) {

	    const auto& swc_info = get_swapchain_info(phys_device,
	                                              surface, loader);
	    const auto& scaps =
	      swc_info.sfc_capabilities.surfaceCapabilities;

	    // Select the swapchain surface format, presentation mode,
	    // and image extent.
	    const auto swc_format = select_format(swc_info.sfc_formats);
	    const auto& swc_pmode = select_present_mode(
	      swc_info.present_modes);
	    const auto swc_extent = select_swap_extent(
	      swc_info.sfc_capabilities, width, height);

	    if (swc_extent.height == 0 || swc_extent.width == 0) {
		throw phx_err::Retry{};
	    }

	    // Select at least one more than the minimum number of
	    // swapchain images, bounded by the maximum.  A maximum
	    // value of 0 indicates unlimited.
	    const auto& min_images = [&] {
		if (scaps.maxImageCount == 0) {
		    // No maximum.
		    return scaps.minImageCount + 1;
		}

		return scaps.minImageCount == scaps.maxImageCount
		         ? scaps.minImageCount
		         : scaps.minImageCount + 1;
	    }();

	    // TODO: Change for stereoscopic rendering.
	    const auto& img_layers = 1;

	    const auto& img_usage =
	      vk::ImageUsageFlagBits::eColorAttachment;

	    const auto& queue_info = get_queue_info(phys_device,
	                                            surface);

	    const auto& [img_sharing_mode, qvec] = [&] {
		using qv = std::vector<uint32_t>;

		const auto& qi = queue_info;
		const auto& gi = *qi.graphics_indices.begin();
		const auto& pi = *qi.presentation_indices.begin();

		if (gi == pi) {
		    return std::make_tuple(vk::SharingMode::eExclusive,
		                           qv{});
		}

		return std::make_tuple(vk::SharingMode::eConcurrent,
		                       qv{ gi, pi });
	    }();

	    const auto& qvec_size = static_cast<uint32_t>(qvec.size());

	    vk::SwapchainCreateInfoKHR swc_props(
	      vk::SwapchainCreateFlagBitsKHR::eProtected, surface,
	      min_images, swc_format.format, swc_format.colorSpace,
	      swc_extent, img_layers, img_usage, img_sharing_mode,
	      qvec_size, qvec.data(), scaps.currentTransform,
	      vk::CompositeAlphaFlagBitsKHR::eOpaque, swc_pmode, true);

	    if (old_swapchain.has_value()) {
		swc_props.oldSwapchain = *old_swapchain;
	    }

	    return std::make_tuple(device.createSwapchainKHR(swc_props),
	                           swc_format, swc_extent);
	}

	std::vector<vk::ImageView>
	make_image_views(const vk::Device&             device,
	                 const std::vector<vk::Image>& images,
	                 const vk::SurfaceFormatKHR&   format) {

	    std::vector<vk::ImageView> result;

	    // TODO: VR support requires subresource ranges with
	    // multiple layers.
	    for (const auto& image : images) {
		result.emplace_back(
		  device.createImageView(vk::ImageViewCreateInfo(
		    vk::ImageViewCreateFlagBits(), image,
		    vk::ImageViewType::e2D, format.format,
		    vk::ComponentMapping(),
		    vk::ImageSubresourceRange(
		      vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1))));
	    }

	    return result;
	}

	void destroy_image_views(const vk::Device&           device,
	                         std::vector<vk::ImageView>& views) {
	    for (const auto& view : views) {
		device.destroyImageView(view);
	    }
	}

	void destroy_framebuffers(const vk::Device&             device,
	                          std::vector<vk::Framebuffer>& fbs) {
	    for (const auto& fb : fbs) {
		device.destroyFramebuffer(fb);
	    }
	}

	template <long unsigned int n>
	void destroy_semaphores(const vk::Device&             device,
	                        std::array<vk::Semaphore, n>& sems) {
	    for (int i = 0; i < n; i++) {
		device.destroySemaphore(sems[i]);
	    }
	}

	template <long unsigned int n>
	void destroy_fences(const vk::Device&         device,
	                    std::array<vk::Fence, n>& fences) {
	    for (int i = 0; i < n; i++) {
		device.destroyFence(fences[i]);
	    }
	}

	std::string render_version(uint32_t encoded) {
	    std::stringstream ss;

	    auto maj = VK_VERSION_MAJOR(encoded);
	    auto min = VK_VERSION_MINOR(encoded);
	    auto pat = VK_VERSION_PATCH(encoded);

	    ss << maj << "." << min << "." << pat;

	    return ss.str();
	}

	std::vector<char> read_all(res::ID id) {
	    const auto& r = res::Mapper::Fetch(id);

	    const auto& len = r->Len();

	    std::vector<char> into(len);

	    size_t consumed = 0;
	    while (consumed < len) {
		consumed += r->Read(into.data() + consumed,
		                    len - consumed);
	    };

	    return into;
	}

	struct ModuleWrapper : public vk::ShaderModule {
	    const vk::Device& device;
	    ModuleWrapper(const vk::Device& device,
	                  vk::ShaderModule  mod)
	        : device(device), vk::ShaderModule(mod) {}
	    ~ModuleWrapper() { device.destroyShaderModule(*this); }
	};

	ModuleWrapper create_module(const vk::Device&        device,
	                            const std::vector<char>& data) {
	    return ModuleWrapper(
	      device,
	      device.createShaderModule(vk::ShaderModuleCreateInfo(
	        vk::ShaderModuleCreateFlags(), data.size(),
	        reinterpret_cast<const uint32_t*>(data.data()))));
	}

    }; // namespace

    // TODO: Refactor to static "builder" and initializer list.
    template class VKRenderer<true>;
    template class VKRenderer<false>;

    template <bool debugging>
    const Uint32 VKRenderer<debugging>::window_flags() noexcept {
	if constexpr (debugging) {
	    return debug_window_flags();
	}

	return SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN |
	       SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_VULKAN |
	       SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_INPUT_FOCUS |
	       SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS;
    }

    template <bool debugging>
    const Uint32 VKRenderer<debugging>::debug_window_flags() noexcept {
	return SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI |
	       SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
    }

    template <bool debugging>
    void VKRenderer<debugging>::post_hooks() noexcept {
	if constexpr (!debugging) {
	    SDL_ShowCursor(false);
	}
    }

    template <bool debugging>
    gfx::extent VKRenderer<debugging>::extent() noexcept {
	return gfx::extent{ width, height };
    }

    template <bool debugging>
    VKRenderer<debugging>::VKRenderer(Window&& w, const Scene& scene_in)
        : window(std::move(w)),
          queue_priority(std::make_unique<float>(1.0f)),
          scene(scene_in),
          app_info(
            std::make_unique<vk::ApplicationInfo>(vk::ApplicationInfo(
              w.get_title(), VK_MAKE_VERSION(0, 0, 1), "Phoenix Engine",
              VK_MAKE_VERSION(0, 0, 1), VK_VERSION_1_1))),
          current_frame(0), frame_count(0), destroyer(this) {

	// TODO: Refactor into "proper RAII" (yikes)

	auto get_ex = SDL_Vulkan_GetInstanceExtensions;

	uint32_t num_extns = 0;

	// Get the number of required extensions.
	if (auto ok = get_ex(window, &num_extns, nullptr); !ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_GetInstanceExtensions failed (get "
	      "count)");
	}

	// Get the required extensions.
	std::vector<const char*> extns(num_extns);
	if (auto ok = get_ex(window, &num_extns, extns.data()); !ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_GetInstanceExtensions failed (get data)");
	}

	// If debugging, list the required extensions.
	if constexpr (debugging) {
	    std::cerr << "SDL_Vulkan_GetInstanceExtensions reported "
	                 "required instance extensions: "
	              << std::endl;
	    for (const auto& e : extns) {
		std::cerr << "  " << e << std::endl;
	    }

	    std::cerr << std::endl
	              << "Phoenix also requires instance extensions:"
	              << std::endl;

	    for (const auto& e : required_inst_extns) {
		std::cerr << "  " << e << std::endl;
	    }

	    std::cerr << std::endl;
	}

	// Add any extensions we know are required.
	for (const auto& extn : required_inst_extns) {
	    extns.emplace_back(extn.data());
	}

	std::vector<const char*> layers;

	// If debugging, add the validation layer and debug utils
	// extension.
	if constexpr (debugging) {
	    // Add the comprehensive Khronos validation combo layer.
	    layers.push_back("VK_LAYER_KHRONOS_validation");
	    // layers.push_back("VK_LAYER_LUNARG_standard_validation");

	    // Add the debug utils extension for error callbacks.
	    extns.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	    // Display the names and versions of available
	    // extensions to stderr.
	    render_available_extns(std::cerr);
	}

	auto size_layers = static_cast<uint32_t>(layers.size());
	auto size_extns  = static_cast<uint32_t>(extns.size());

	// Create the Vulkan instance handle.
	instance = vk::createInstance(vk::InstanceCreateInfo(
	  vk::InstanceCreateFlags(), app_info.get(), size_layers,
	  layers.data(), size_extns, extns.data()));

	dyn_loader = vk::DispatchLoaderDynamic(
	  instance.operator VkInstance(),
	  PFN_vkGetInstanceProcAddr(
	    SDL_Vulkan_GetVkGetInstanceProcAddr()));
	// dyn_loader = vk::DispatchLoaderDynamic(instance);

	// If debugging, set up the debug messenger.
	if constexpr (debugging) {
	    // Use the C++ constructor to make sure the Messenger
	    // CreateInfo is correct.
	    auto msgr_props = vk::DebugUtilsMessengerCreateInfoEXT(
	      vk::DebugUtilsMessengerCreateFlagsEXT(),
	      debug_utils_severity, debug_utils_msgtype,
	      &debug_utils_log_message, nullptr);

	    debug_messenger = instance.createDebugUtilsMessengerEXT(
	      msgr_props, nullptr, dyn_loader);
	}

	// Get the list of available physical devices.
	auto devices = instance.enumeratePhysicalDevices();
	if (devices.size() == 0) {
	    throw phx_err::InitError(
	      "no graphics devices support Vulkan");
	}

	VkSurfaceKHR vksfc;
	auto ok = SDL_Vulkan_CreateSurface(window, instance, &vksfc);
	if (!ok) {
	    throw phx_err::SDLInitError(
	      "SDL_Vulkan_CreateSurface failed");
	}

	surface = vk::SurfaceKHR(vksfc);

	// Rank them in a multimap, so the highest-ranked one comes
	// first.
	auto device_rank_to_index =
	  get_ranks<debugging, std::greater<uint32_t>>(devices, surface,
	                                               dyn_loader);
	if (std::get<0>(*device_rank_to_index.begin()) == 0) {
	    throw phx_err::InitError(
	      "no acceptable graphics devices found");
	}

	// The highest-ranked one comes first, so select the
	// physical device having the index it was associated with.
	phys_device =
	  devices[std::get<1>(*device_rank_to_index.begin())];

	// If debugging, log the name of the selected device.
	if constexpr (debugging) {
	    const auto& device_props =
	      phys_device.getProperties2().properties;
	    std::cerr << "Selected graphics device: "
	              << device_props.deviceName << " (Vulkan "
	              << render_version(device_props.apiVersion)
	              << ": Driver "
	              << render_version(device_props.driverVersion)
	              << ")" << std::endl
	              << std::endl;
	}

	// Get the capabilities of the device's queue families.
	auto queue_info = get_queue_info(phys_device, surface);

	// Set up the CreateInfo for the DeviceQueues which we want,
	// having the "graphics" and "presentation" capabilities.
	auto graphics_queue_index = *(
	  queue_info.graphics_indices.begin());
	auto presentation_queue_index = *(
	  queue_info.presentation_indices.begin());

	// Always use the graphics queue.
	std::vector<vk::DeviceQueueCreateInfo> queue_props{
	    vk::DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(),
	                              graphics_queue_index, 1,
	                              queue_priority.get())
	};

	// If the presentation queue is different, add that too.
	if (presentation_queue_index != graphics_queue_index) {
	    queue_props.push_back(vk::DeviceQueueCreateInfo(
	      vk::DeviceQueueCreateFlags(), presentation_queue_index, 1,
	      queue_priority.get()));
	}

	auto queue_props_size = static_cast<uint32_t>(
	  queue_props.size());

	// Set up the required device features.  Right now we don't
	// really care what features it has.
	auto features = phys_device.getFeatures2();

	// Set up the required extensions.
	std::vector<const char*> dev_extns;
	for (const auto& extn : required_dev_extns) {
	    dev_extns.emplace_back(extn.data());
	}

	const auto len_dev_extns = static_cast<uint32_t>(
	  dev_extns.size());

	device = phys_device.createDevice(vk::DeviceCreateInfo(
	  vk::DeviceCreateFlags(), queue_props_size, queue_props.data(),
	  0, nullptr, len_dev_extns, dev_extns.data(),
	  &features.features));

	grph_queue = device.getQueue(graphics_queue_index, 0);
	// Note that pres_queue might just be an alias of
	// grph_queue, and that's ok.
	pres_queue = device.getQueue(presentation_queue_index, 0);

	SDL_Vulkan_GetDrawableSize(window, &width, &height);

	// If the drawable is zero-sized, we can't set up a sane
	// swapchain.
	if (width == 0 || height == 0) {
	    // TODO: Get rid of stupid throws.
	    std::stringstream ss;
	    ss << "SDL_Vulkan_GetDrawableSize got zero-sized drawable: "
	       << "(" << width << ", " << height << ")";
	    throw phx_err::InitError(ss);
	}

	// create_swapchain returns a tuple with the swapchain along
	// with its format and extent, so unpack that using std::tie.
	std::tie(swapchain, swc_format, swc_extent) = create_swapchain(
	  phys_device, device, surface, dyn_loader, width, height);

	swc_images = device.getSwapchainImagesKHR(swapchain);

	swc_image_views = make_image_views(device, swc_images,
	                                   swc_format);

	///////////////////// SHADER DEPENDENT /////////////////////////
	// Load shader data and create modules.
	////////////////////////////////////////////////////////////////
	// Make fragment and vertex stage configs using these modules.
	// Make list of shader stage configs for the shader pipeline.
	// Make vertex input config with bindings and attributes.
	//  (Not used for static scenes.)
	// Make input assembly state config, with vertex primitive
	//   topology.  This controls how the pipeline will assemble
	//   primitives (such as triangles) from vertices.
	// Make the viewport state config with fullscreen scissor.
	// Make the rasterization state config with optional depth clamp
	//   and discard, poly mode, cull mode, front face mode, etc.
	// Make the multisample state config.
	// Make the color blend attachment and state configs.
	// Create the pipeline layout on the device.
	// Get the Vulkan dynamic dispatch handle from the instance.
	// Make the render pass config.
	//   - Make the color attachment description & reference configs
	//   - Make the subpass config
	//   - Make the subpass dependencies config
	// Create the render pass on the device.
	// Create the pipeline cache on the device.
	// Create the pipeline on the device, caching it.
	//   - Shader stages
	//   - Vertex input config
	//   - Input assembly config
	//   - Viewport config
	//   - Rasterizer config
	//   - Multisampling config
	//   - Color blending config
	//   - Pipeline layout
	//   - Render pass
	// For each swapchain image view, create a new framebuffer on
	//   the device using the render pass.
	// Create a command pool and allocate command buffers on the
	//   device, on its graphics queue.
	// For each command buffer, encode a new draw command.
	const auto& frag_data   = read_all(scene.shader().frag);
	const auto& vert_data   = read_all(scene.shader().vert);
	const auto& frag_module = create_module(device, frag_data);
	const auto& vert_module = create_module(device, vert_data);

	// Note that the name must be the name of the entrypoint
	// function in the shader.
	const auto& frag_stage_config =
	  vk::PipelineShaderStageCreateInfo(
	    vk::PipelineShaderStageCreateFlags(),
	    vk::ShaderStageFlagBits::eFragment, frag_module, "main");

	const auto& vert_stage_config =
	  vk::PipelineShaderStageCreateInfo(
	    vk::PipelineShaderStageCreateFlags(),
	    vk::ShaderStageFlagBits::eVertex, vert_module, "main");

	std::vector<vk::PipelineShaderStageCreateInfo> shader_stages = {
	    vert_stage_config, frag_stage_config
	};

	vk::PipelineVertexInputStateCreateInfo vertex_input_config(
	  vk::PipelineVertexInputStateCreateFlags(), 0, nullptr, 0,
	  nullptr);

	vk::PipelineInputAssemblyStateCreateInfo input_assembly_config(
	  vk::PipelineInputAssemblyStateCreateFlags(),
	  vk::PrimitiveTopology::eTriangleList);

	float wf = static_cast<float>(swc_extent.width);
	float hf = static_cast<float>(swc_extent.height);

	const auto& viewport = vk::Viewport(0.0f, 0.0f, wf, hf, 0.0f,
	                                    1.0f);

	vk::Rect2D scissor(vk::Offset2D(), swc_extent);

	vk::PipelineViewportStateCreateInfo viewport_config(
	  vk::PipelineViewportStateCreateFlags(), 1, &viewport, 1,
	  &scissor);

	vk::PipelineRasterizationStateCreateInfo rasterizer_config(
	  vk::PipelineRasterizationStateCreateFlags(), false, false,
	  vk::PolygonMode::eFill,
	  vk::CullModeFlags(vk::CullModeFlagBits::eBack),
	  vk::FrontFace::eClockwise, false, 0.0f, 0.0f, 0.0f, 1.0f);

	vk::PipelineMultisampleStateCreateInfo multisample_config(
	  vk::PipelineMultisampleStateCreateFlags(),
	  vk::SampleCountFlagBits::e1, false, 1.0f, nullptr, false,
	  false);

	// vk::PipelineDepthStencilStateCreateInfo();

	// Configure color blending.
	auto f0    = vk::BlendFactor::eZero;
	auto f1    = vk::BlendFactor::eOne;
	auto fsa   = vk::BlendFactor::eSrcAlpha;
	auto f1msa = vk::BlendFactor::eOneMinusSrcAlpha;
	auto add   = vk::BlendOp::eAdd;
	auto all_color_components =
	  vk::FlagTraits<vk::ColorComponentFlagBits>::allFlags;
	vk::PipelineColorBlendAttachmentState color_blend_attachment(
	  true, fsa, f1msa, add, f1, f0, add,
	  vk::ColorComponentFlags(all_color_components));

	vk::PipelineColorBlendStateCreateInfo blend_config(
	  vk::PipelineColorBlendStateCreateFlags(), false,
	  vk::LogicOp::eCopy, 1, &color_blend_attachment);

	/* If the viewport is expected to have dynamic state:
	std::vector<vk::DynamicState> dyn_states = {
	    vk::DynamicState::eViewport, vk::DynamicState::eLineWidth
	};
	vk::PipelineDynamicStateCreateInfo(
	  vk::PipelineDynamicStateCreateFlags(), 2, dyn_states.data());
	*/

	pl_layout = device.createPipelineLayout(
	  vk::PipelineLayoutCreateInfo(vk::PipelineLayoutCreateFlags()),
	  nullptr, dyn_loader);

	dyn_loader = vk::DispatchLoaderDynamic(
	  instance.operator VkInstance(),
	  PFN_vkGetInstanceProcAddr(
	    SDL_Vulkan_GetVkGetInstanceProcAddr()),
	  device, vkGetDeviceProcAddr);

	vk::AttachmentDescription2KHR color_attachment_descr(
	  vk::AttachmentDescriptionFlags(), swc_format.format,
	  vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear,
	  vk::AttachmentStoreOp::eStore,
	  vk::AttachmentLoadOp::eDontCare,
	  vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined,
	  vk::ImageLayout::ePresentSrcKHR);

	vk::AttachmentReference2KHR color_attachment_ref(
	  0, vk::ImageLayout::eColorAttachmentOptimal);

	vk::SubpassDescription2KHR subpass(
	  vk::SubpassDescriptionFlags(),
	  vk::PipelineBindPoint::eGraphics, 0, 0, nullptr, 1,
	  &color_attachment_ref);

	vk::SubpassDependency2KHR subpass_dep(
	  VK_SUBPASS_EXTERNAL, 0,
	  vk::PipelineStageFlagBits::eColorAttachmentOutput,
	  vk::PipelineStageFlagBits::eColorAttachmentOutput,
	  vk::AccessFlags(),
	  vk::AccessFlagBits::eColorAttachmentRead |
	    vk::AccessFlagBits::eColorAttachmentWrite,
	  vk::DependencyFlags(), 0);

	vk::RenderPassCreateInfo2KHR render_pass_config(
	  vk::RenderPassCreateFlags(), 1, &color_attachment_descr, 1,
	  &subpass, 1, &subpass_dep);

	render_pass = device.createRenderPass2KHR(render_pass_config,
	                                          nullptr, dyn_loader);
	pl_cache    = device.createPipelineCache(
          vk::PipelineCacheCreateInfo());

	pipeline = device.createGraphicsPipeline(
	  pl_cache,
	  vk::GraphicsPipelineCreateInfo(
	    vk::PipelineCreateFlags(), 2, shader_stages.data(),
	    &vertex_input_config, &input_assembly_config, nullptr,
	    &viewport_config, &rasterizer_config, &multisample_config,
	    nullptr, &blend_config, nullptr, pl_layout, render_pass, 0,
	    vk::Pipeline(), 0));

	for (const auto& view : swc_image_views) {
	    swc_framebuffers.emplace_back(
	      device.createFramebuffer(vk::FramebufferCreateInfo(
	        vk::FramebufferCreateFlags(), render_pass, 1, &view,
	        swc_extent.width, swc_extent.height, 1)));
	}

	cmd_pool = device.createCommandPool(vk::CommandPoolCreateInfo(
	  vk::CommandPoolCreateFlags(), graphics_queue_index));

	cmd_buffers = device.allocateCommandBuffers(
	  vk::CommandBufferAllocateInfo(
	    cmd_pool, vk::CommandBufferLevel::ePrimary,
	    static_cast<uint32_t>(swc_framebuffers.size())));

	for (int i = 0; i < swc_framebuffers.size(); i++) {
	    const auto& cb = cmd_buffers[i];

	    // Begin a new command.
	    cb.begin(vk::CommandBufferBeginInfo(
	      vk::CommandBufferUsageFlagBits::eSimultaneousUse));

	    // Use the scene's renderpass encoder.
	    scene.encode_renderpass(cb, dyn_loader, render_pass,
	                            swc_framebuffers[i], swc_extent,
	                            pipeline, DEVICE_MASK);

	    cb.end();
	}

	for (int i = 0; i < max_frames_inflight; i++) {
	    const auto& sem_cfg   = vk::SemaphoreCreateInfo();
	    const auto& sig       = vk::FenceCreateFlagBits::eSignaled;
	    const auto& fence_cfg = vk::FenceCreateInfo(sig);

	    img_ready[i]       = device.createSemaphore(sem_cfg);
	    render_done[i]     = device.createSemaphore(sem_cfg);
	    inflight_fences[i] = device.createFence(fence_cfg);
	}
    }

    template <bool debugging>
    VKRenderer<debugging>::VKRenderer(VKRenderer&& from) noexcept
        : destroyer(std::move(from.destroyer)),

          window(std::move(from.window)),
          instance(std::move(from.instance)),

          phys_device(std::move(from.phys_device)),
          device(std::move(from.device)),

          grph_queue(std::move(from.grph_queue)),
          pres_queue(std::move(from.pres_queue)),

          surface(std::move(from.surface)),
          pl_cache(std::move(from.pl_cache)),
          pipeline(std::move(from.pipeline)),
          pl_layout(std::move(from.pl_layout)),

          swapchain(std::move(from.swapchain)),
          swc_format(std::move(from.swc_format)),
          swc_extent(std::move(from.swc_extent)),
          swc_images(std::move(from.swc_images)),
          swc_image_views(std::move(from.swc_image_views)),
          swc_framebuffers(std::move(from.swc_framebuffers)),

          render_pass(std::move(from.render_pass)),

          cmd_pool(std::move(from.cmd_pool)),
          cmd_buffers(std::move(from.cmd_buffers)),

          current_frame(from.current_frame),

          img_ready(std::move(from.img_ready)),
          render_done(std::move(from.render_done)),
          inflight_fences(std::move(from.inflight_fences)),

          last_frame_time(std::move(from.last_frame_time)),
          frame_count(std::move(from.frame_count)),

          // Resources that need dynamic lifetime and constant address.
          queue_priority(std::move(from.queue_priority)),
          app_info(std::move(from.app_info)),

          // Resources that exist outside of the Renderer's lifetime.
          scene(from.scene),

          width(std::move(from.width)), height(std::move(from.height)),

          debug_messenger(std::move(from.debug_messenger)),
          dyn_loader(std::move(from.dyn_loader)) {

	// Note: this is necessary because the old location becomes
	// invalid after the move.  Destroyer is a std::unique_ptr
	// responsible for cleaning up the VKRenderer's resources,
	// which will only happen when it is finally destroyed.

	// TODO: Migrate to C++20 "std::resource" or whatever it's
	// called.

	destroyer.release();
	destroyer.reset(this);
    }

    template <bool debugging>
    void VKRenderer<debugging>::update() {}

    template <bool debugging>
    void VKRenderer<debugging>::draw(std::nullptr_t) {
	size_t c = current_frame;

	// Fences are created in a signaled state, so this will always
	// succeed until they are reset.  They will only be reset
	// immediately before queue submission, which signals them upon
	// completion.
	device.waitForFences(inflight_fences[c], true,
	                     std::numeric_limits<uint64_t>::max());

	// TODO: Refactor to avoid giant try/catch.
	// TODO: Understand why this is slow.
	// TODO: Understand why Intel integrated GPU does not invalidate
	// on resize.
	try {
	    // Get the index of the swapchain image to use.
	    const auto& result = device.acquireNextImage2KHR(
	      vk::AcquireNextImageInfoKHR(
	        swapchain, std::numeric_limits<uint64_t>::max(),
	        img_ready[c], vk::Fence(), DEVICE_MASK));

	    switch (result.result) {
	    case vk::Result::eSuccess:
		break;

	    /*
	    case vk::Result::eTimeout:
	    case vk::Result::eNotReady:
	    */
	    default:
		throw result.result;
	    }

	    const auto& i = result.value;

	    vk::PipelineStageFlags stages(
	      vk::PipelineStageFlagBits::eColorAttachmentOutput);

	    vk::SubmitInfo submit_configs(1, &img_ready[c], &stages, 1,
	                                  &cmd_buffers[i], 1,
	                                  &render_done[c]);

	    vk::PresentInfoKHR present_config(1, &render_done[c], 1,
	                                      &swapchain, &i);

	    // Only reset fences immediately before queue submission.
	    device.resetFences(inflight_fences[c]);

	    grph_queue.submit(submit_configs, inflight_fences[c]);
	    const auto& pres_result = pres_queue.presentKHR(
	      present_config);

	    switch (pres_result) {
	    case vk::Result::eSuccess:
		break;

	    default:
		throw result.result;
	    }

	} catch ([[maybe_unused]] vk::Result& e) {
	    // This is a soft failure that could have been saved, but we
	    // just haven't handled this case yet.
	    if constexpr (debugging) {
		std::cerr << "Soft failure in draw: " << e << std::endl;
	    }

	    reload_swapchain();
	    throw phx_err::Retry{};

	} catch ([[maybe_unused]] vk::OutOfDateKHRError& e) {
	    // Exceptional renderer results mean the swapchain needs to
	    // be rebuilt.  If the reload fails, re-throw.
	    // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#fundamentals-errorcodes
	    //
	    // VK_ERROR_OUT_OF_DATE_KHR A surface has changed in such a
	    // way that it is no longer compatible with the swapchain,
	    // and further presentation requests using the swapchain
	    // will fail. Applications must query the new surface
	    // properties and recreate their swapchain if they wish to
	    // continue presenting to the surface.
	    if constexpr (debugging) {
		std::cerr << "Swapchain expired: " << e.what()
		          << std::endl;
	    }

	    // If this fails, it will throw.
	    reload_swapchain();
	    throw phx_err::Retry{};
	}

	// If everything succeeded, update frame metrics.
	if constexpr (debugging) {
	    frame_count++;
	    const auto& this_frame_time =
	      std::chrono::high_resolution_clock::now();
	    if (frame_count % 100 == 0) {
		std::cerr
		  << "Frame time: " << std::setprecision(3)
		  << (this_frame_time - last_frame_time).count() /
		       1000000.0
		  << "ms" << std::endl;
	    }
	    last_frame_time = this_frame_time;
	}

	current_frame = (c + 1) % max_frames_inflight;

    } // namespace phx_sdl

    template <bool debugging>
    void VKRenderer<debugging>::reload_swapchain() {
	// TODO: DRY up between this and full teardown.
	device.waitIdle();

	// First, clean up any transient resources.
	destroy_framebuffers(device, swc_framebuffers);
	device.freeCommandBuffers(cmd_pool, cmd_buffers);

	device.destroyPipeline(pipeline);
	device.destroyPipelineLayout(pl_layout);

	// TODO: Can / should we cache the pipeline for later?
	device.destroyPipelineCache(pl_cache);

	device.destroyRenderPass(render_pass, nullptr, dyn_loader);
	destroy_image_views(device, swc_image_views);

	/* This stuff is only for full teardown.
	        destroy_semaphores(device, render_done);
	        destroy_semaphores(device, img_ready);
	        destroy_fences(device, inflight_fences);
	        device.destroyCommandPool(cmd_pool);
	        device.destroy();
	        if constexpr (debugging) {
	            instance.destroyDebugUtilsMessengerEXT(debug_messenger,
	                                                   nullptr,
	   dyn_loader);
	        }

	        instance.destroy();
	        */

	vk::SwapchainKHR tmp_swapchain;

	while (true) {
	    // TODO: DRY this up with initial creation?
	    // Then, reload the full swapchain:
	    try {
		int width  = 0;
		int height = 0;
		SDL_Vulkan_GetDrawableSize(window, &width, &height);
		if (width == 0 || height == 0) {
		    // If the drawable is zero-sized, we can't set up a
		    // sane swapchain.
		    throw phx_err::Retry{};
		}

		std::tie(tmp_swapchain, swc_format, swc_extent) =
		  create_swapchain(phys_device, device, surface,
		                   dyn_loader, width, height,
		                   swapchain);
	    } catch ([[maybe_unused]] phx_err::Retry& r) {
		continue;
	    }

	    break;
	}

	device.destroySwapchainKHR(swapchain);

	swapchain = tmp_swapchain;

	// TODO: Refactor to DRY up all this stuff.
	swc_images      = device.getSwapchainImagesKHR(swapchain);
	swc_image_views = make_image_views(device, swc_images,
	                                   swc_format);

	const auto& frag_data   = read_all(scene.shader().frag);
	const auto& vert_data   = read_all(scene.shader().vert);
	const auto& frag_module = create_module(device, frag_data);
	const auto& vert_module = create_module(device, vert_data);

	// Note that the name must be the name of the entrypoint
	// function in the shader.
	const auto& frag_stage_config =
	  vk::PipelineShaderStageCreateInfo(
	    vk::PipelineShaderStageCreateFlags(),
	    vk::ShaderStageFlagBits::eFragment, frag_module, "main");

	const auto& vert_stage_config =
	  vk::PipelineShaderStageCreateInfo(
	    vk::PipelineShaderStageCreateFlags(),
	    vk::ShaderStageFlagBits::eVertex, vert_module, "main");

	std::vector<vk::PipelineShaderStageCreateInfo> shader_stages = {
	    vert_stage_config, frag_stage_config
	};

	vk::PipelineVertexInputStateCreateInfo vertex_input_config(
	  vk::PipelineVertexInputStateCreateFlags(), 0, nullptr, 0,
	  nullptr);

	vk::PipelineInputAssemblyStateCreateInfo input_assembly_config(
	  vk::PipelineInputAssemblyStateCreateFlags(),
	  vk::PrimitiveTopology::eTriangleList);

	float wf = static_cast<float>(swc_extent.width);
	float hf = static_cast<float>(swc_extent.height);

	const auto& viewport = vk::Viewport(0.0f, 0.0f, wf, hf, 0.0f,
	                                    1.0f);

	vk::Rect2D scissor(vk::Offset2D(), swc_extent);

	vk::PipelineViewportStateCreateInfo viewport_config(
	  vk::PipelineViewportStateCreateFlags(), 1, &viewport, 1,
	  &scissor);

	vk::PipelineRasterizationStateCreateInfo rasterizer_config(
	  vk::PipelineRasterizationStateCreateFlags(), false, false,
	  vk::PolygonMode::eFill,
	  vk::CullModeFlags(vk::CullModeFlagBits::eBack),
	  vk::FrontFace::eClockwise, false, 0.0f, 0.0f, 0.0f, 1.0f);

	vk::PipelineMultisampleStateCreateInfo multisample_config(
	  vk::PipelineMultisampleStateCreateFlags(),
	  vk::SampleCountFlagBits::e1, false, 1.0f, nullptr, false,
	  false);

	// vk::PipelineDepthStencilStateCreateInfo();

	// Configure color blending.
	auto f0    = vk::BlendFactor::eZero;
	auto f1    = vk::BlendFactor::eOne;
	auto fsa   = vk::BlendFactor::eSrcAlpha;
	auto f1msa = vk::BlendFactor::eOneMinusSrcAlpha;
	auto add   = vk::BlendOp::eAdd;
	auto all_color_components =
	  vk::FlagTraits<vk::ColorComponentFlagBits>::allFlags;
	vk::PipelineColorBlendAttachmentState color_blend_attachment(
	  true, fsa, f1msa, add, f1, f0, add,
	  vk::ColorComponentFlags(all_color_components));

	vk::PipelineColorBlendStateCreateInfo blend_config(
	  vk::PipelineColorBlendStateCreateFlags(), false,
	  vk::LogicOp::eCopy, 1, &color_blend_attachment);

	pl_layout = device.createPipelineLayout(
	  vk::PipelineLayoutCreateInfo(vk::PipelineLayoutCreateFlags()),
	  nullptr, dyn_loader);

	vk::AttachmentDescription2KHR color_attachment_descr(
	  vk::AttachmentDescriptionFlags(), swc_format.format,
	  vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear,
	  vk::AttachmentStoreOp::eStore,
	  vk::AttachmentLoadOp::eDontCare,
	  vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined,
	  vk::ImageLayout::ePresentSrcKHR);

	vk::AttachmentReference2KHR color_attachment_ref(
	  0, vk::ImageLayout::eColorAttachmentOptimal);
	vk::SubpassDescription2KHR subpass(
	  vk::SubpassDescriptionFlags(),
	  vk::PipelineBindPoint::eGraphics, 0, 0, nullptr, 1,
	  &color_attachment_ref);

	vk::SubpassDependency2KHR subpass_dep(
	  VK_SUBPASS_EXTERNAL, 0,
	  vk::PipelineStageFlagBits::eColorAttachmentOutput,
	  vk::PipelineStageFlagBits::eColorAttachmentOutput,
	  vk::AccessFlags(),
	  vk::AccessFlagBits::eColorAttachmentRead |
	    vk::AccessFlagBits::eColorAttachmentWrite,
	  vk::DependencyFlags(), 0);

	vk::RenderPassCreateInfo2KHR render_pass_config(
	  vk::RenderPassCreateFlags(), 1, &color_attachment_descr, 1,
	  &subpass, 1, &subpass_dep);

	render_pass = device.createRenderPass2KHR(render_pass_config,
	                                          nullptr, dyn_loader);

	pl_cache = device.createPipelineCache(
	  vk::PipelineCacheCreateInfo());

	// TODO: Isolate crash here.
	pipeline = device.createGraphicsPipeline(
	  pl_cache,
	  vk::GraphicsPipelineCreateInfo(
	    vk::PipelineCreateFlags(), 2, shader_stages.data(),
	    &vertex_input_config, &input_assembly_config, nullptr,
	    &viewport_config, &rasterizer_config, &multisample_config,
	    nullptr, &blend_config, nullptr, pl_layout, render_pass, 0,
	    vk::Pipeline(), 0));

	// TODO: Remove redundant bits.
	swc_framebuffers.clear();
	for (const auto& view : swc_image_views) {
	    swc_framebuffers.emplace_back(
	      device.createFramebuffer(vk::FramebufferCreateInfo(
	        vk::FramebufferCreateFlags(), render_pass, 1, &view,
	        swc_extent.width, swc_extent.height, 1)));
	}

	// Get the capabilities of the device's queue families.
	auto queue_info = get_queue_info(phys_device, surface);

	auto graphics_queue_index = *(
	  queue_info.graphics_indices.begin());

	cmd_buffers = device.allocateCommandBuffers(
	  vk::CommandBufferAllocateInfo(
	    cmd_pool, vk::CommandBufferLevel::ePrimary,
	    static_cast<uint32_t>(swc_framebuffers.size())));

	for (int i = 0; i < swc_framebuffers.size(); i++) {
	    const auto& cb = cmd_buffers[i];

	    cb.begin(vk::CommandBufferBeginInfo(
	      vk::CommandBufferUsageFlagBits::eSimultaneousUse));

	    // Use the scene's renderpass encoder.
	    scene.encode_renderpass(cb, dyn_loader, render_pass,
	                            swc_framebuffers[i], swc_extent,
	                            pipeline, DEVICE_MASK);

	    cb.end();
	}

	/*
	for (int i = 0; i < max_frames_inflight; i++) {
	    const auto& sem_cfg   = vk::SemaphoreCreateInfo();
	    const auto& sig       = vk::FenceCreateFlagBits::eSignaled;
	    const auto& fence_cfg = vk::FenceCreateInfo(sig);

	    img_ready[i]       = device.createSemaphore(sem_cfg);
	    render_done[i]     = device.createSemaphore(sem_cfg);
	    inflight_fences[i] = device.createFence(fence_cfg);
	}
	*/
    }

    template <bool debugging>
    void VKRenderer<debugging>::clear() {}

    template <bool debugging>
    void VKRenderer<debugging>::teardown() {
	device.waitIdle();

	destroy_semaphores(device, img_ready);
	destroy_semaphores(device, render_done);
	destroy_fences(device, inflight_fences);

	device.destroyCommandPool(cmd_pool);
	device.destroyRenderPass(render_pass, nullptr, dyn_loader);
	device.destroyPipeline(pipeline);
	destroy_framebuffers(device, swc_framebuffers);
	device.destroyPipelineCache(pl_cache);
	device.destroyPipelineLayout(pl_layout);

	destroy_image_views(device, swc_image_views);

	device.destroySwapchainKHR(swapchain);

	device.destroy();

	if constexpr (debugging) {
	    instance.destroyDebugUtilsMessengerEXT(debug_messenger,
	                                           nullptr, dyn_loader);
	}

	instance.destroy();
    }

} // namespace phx_sdl
