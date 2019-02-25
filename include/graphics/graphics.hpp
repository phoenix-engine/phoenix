#ifndef PHX_GRAPHICS_HPP
#define PHX_GRAPHICS_HPP

#include "init_error.hpp"
#include "window.hpp"

namespace gfx {

    template <class R>
    class Graphics {
    public:
	Graphics(R& r, int w, int h) noexcept(false);

	void update();
	void draw();
	void clear();

	// TODO: Build a better drawing API.
	inline void drawPoint(int x, int y, int color) {
	    if (x > 0 && x < w - 1 && y > 0 && y < h - 1) {
		renderer.drawPoint(x, y, color);
	    }
	}

	void drawBlob(int x, int y, int r, int color);

	void drawLine(int x1, int y1, int x2, int y2);

    private:
	int w;
	int h;

	R renderer;
    };

} // namespace gfx

#endif
