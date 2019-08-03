#ifndef PHX_GFX_RENDERER_HPP
#define PHX_GFX_RENDERER_HPP

namespace gfx {

    /**
     * Renderer is an interface for renderer implementations; that is,
     * it specifies an API which Phoenix uses to visualize entities.
     *
     * The intent of the Renderer is not to be used with dynamic
     * implementations, but rather to specify the API expected for
     * renderers.
     */
    class Renderer {
    public:
	Renderer() noexcept(false);

	// postHooks defines the post-setup hooks to call, e.g. for
	// configuring OpenGL / Vulkan context, loading function
	// pointers, etc.
	static void postHooks() noexcept(true);

	virtual void update();
	virtual void draw();
	virtual void clear();

	virtual void drawPoint(int x, int y, int color);
    };

} // namespace gfx

#endif // PHX_GFX_RENDERER_HPP
