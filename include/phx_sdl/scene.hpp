#ifndef PHX_SDL_SCENE_HPP
#define PHX_SDL_SCENE_HPP

#include <memory>
#include <vector>

#include <vulkan/vulkan.hpp>

#include <glm/vec2.hpp>

#include <id.hpp>

namespace phx_sdl {

    class Scene {

    public:
	struct Surface {
	    std::vector<glm::vec2> verts;
	};

	struct Shader {
	    res::ID frag;
	    res::ID vert;
	};

	Surface surface;

	virtual Shader shader(void) const noexcept = 0;

	virtual void encode_renderpass(
	  const vk::CommandBuffer&         into,
	  const vk::DispatchLoaderDynamic& loader,
	  const vk::RenderPass& pass, const vk::Framebuffer& fb,
	  const vk::Extent2D& extent, const vk::Pipeline& pipeline,
	  const uint32_t device_mask) const noexcept = 0;
    };

    class Triangle : public Scene {
    public:
	Shader shader(void) const noexcept override;

	void encode_renderpass(const vk::CommandBuffer&         into,
	                       const vk::DispatchLoaderDynamic& loader,
	                       const vk::RenderPass&            pass,
	                       const vk::Framebuffer&           fb,
	                       const vk::Extent2D&              extent,
	                       const vk::Pipeline& pipeline,
	                       const uint32_t      device_mask) const
	  noexcept override;
    };

    class PushConstants : public Scene {
    public:
	Shader shader(void) const noexcept override;

	void encode_renderpass(const vk::CommandBuffer&         into,
	                       const vk::DispatchLoaderDynamic& loader,
	                       const vk::RenderPass&            pass,
	                       const vk::Framebuffer&           fb,
	                       const vk::Extent2D&              extent,
	                       const vk::Pipeline& pipeline,
	                       const uint32_t      device_mask) const
	  noexcept override;
    };

    class DefaultScenes {
    public:
	DefaultScenes() = delete;

	static const Triangle      triangle;
	static const PushConstants pushconstants;
    };

} // namespace phx_sdl

#endif // PHX_SDL_SCENE_HPP