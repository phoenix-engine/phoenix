#ifndef PHX_GFX_GRAPHICS_HPP
#define PHX_GFX_GRAPHICS_HPP

#include <cmath>

#include "event.hpp"
#include "init_error.hpp"

namespace gfx {

    template <class Renderer, class RenderPayload = std::nullptr_t>
    class Graphics {
    public:
	Graphics() = default;
	Graphics(Renderer&& r, int width, int height) noexcept(true);

	void update(const event::EventIntent&);
	void draw(RenderPayload);
	void clear();

	// TODO: Build a better drawing API.
	inline void drawPoint(int x, int y, int color) {
	    if (x > 0 && x < w - 1 && y > 0 && y < h - 1) {
		renderer.drawPoint(x, y, color);
	    }
	}

	void drawBlob(int x, int y, int r, int color);

	void drawLine(int x1, int y1, int x2, int y2);

	struct Metrics {
	    typename Renderer::Metrics renderer;
	};

	Metrics get_metrics() noexcept;

    private:
	int w;
	int h;

	Renderer renderer;
    };

#include "impl/graphics_impl.hxx"

} // namespace gfx

#endif // PHX_GFX_GRAPHICS_HPP
