#include <id.hpp>

#include "phx_sdl/scene.hpp"

namespace phx_sdl {

    void Triangle::encode_renderpass(
      const vk::CommandBuffer&         into,
      const vk::DispatchLoaderDynamic& loader,
      const vk::RenderPass& pass, const vk::Framebuffer& fb,
      const vk::Extent2D& extent, const vk::Pipeline& pipeline,
      const uint32_t device_mask) const noexcept {

	// Make a clearcolor config.
	vk::ClearValue ccol(vk::ClearColorValue(
	  std::array<float, 4>{ 0.0f, 0.0f, 0.0f, 1.0f }));

	// Set the device mask.
	into.setDeviceMaskKHR(device_mask, loader);

	// Begin a new render pass over the whole extent.
	into.beginRenderPass(
	  vk::RenderPassBeginInfo(
	    pass, fb, vk::Rect2D({ 0, 0 }, extent), 1, &ccol),
	  vk::SubpassContents::eInline);

	// Bind the graphics pipeline.
	into.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
	// Draw 3 vertices.
	into.draw(3, 1, 0, 0);
	// End the render pass.
	into.endRenderPass();
    }

    Scene::Shader Triangle::shader(void) const noexcept {
	return Scene::Shader{ res::ID::triangle_frag_spv,
	                      res::ID::triangle_vert_spv };
    };

    void World2d::encode_renderpass(
      const const vk::CommandBuffer&   into,
      const vk::DispatchLoaderDynamic& loader,
      const vk::RenderPass& pass, const vk::Framebuffer& fb,
      const vk::Extent2D& extent, const vk::Pipeline& pipeline,
      const uint32_t device_mask) const noexcept {

	// Make a clearcolor config.
	vk::ClearValue ccol(vk::ClearColorValue(
	  std::array<float, 4>{ 0.0f, 0.0f, 0.0f, 1.0f }));

	// Set the device mask.
	into.setDeviceMaskKHR(device_mask, loader);

	// Begin a new render pass over the whole extent.
	into.beginRenderPass(
	  vk::RenderPassBeginInfo(
	    pass, fb, vk::Rect2D({ 0, 0 }, extent), 1, &ccol),
	  vk::SubpassContents::eInline);

	// Bind the graphics pipeline.
	into.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
	// Draw 6 vertices.
	into.draw(6, 1, 0, 0);
	// End the render pass.
	into.endRenderPass();
    }

    Scene::Shader World2d::shader(void) const noexcept {
	return Scene::Shader{ res::ID::world2d_frag_spv,
	                      res::ID::world2d_vert_spv };
    };

    const Triangle DefaultScenes::triangle{};
    const World2d  DefaultScenes::world2d{};

} // namespace phx_sdl