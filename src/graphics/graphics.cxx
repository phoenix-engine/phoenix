#include <cmath>

#include "graphics.hpp"

#include "gl_renderer.hpp"
#include "sdl_renderer.hpp"
#include "window.hpp"

namespace gfx {

    template <class R>
    Graphics<R>::Graphics(sdl::Window& winIn, int wIn,
                          int hIn) noexcept(false)
        : w(wIn), h(hIn), renderer(winIn.handle(), wIn, hIn) {}

    template <class R>
    void Graphics<R>::update() {
	renderer.update();
    }

    template <class R>
    void Graphics<R>::draw() {
	renderer.draw();
    }

    template <class R>
    void Graphics<R>::clear() {
	renderer.clear();
    }

    template <class R>
    void Graphics<R>::drawLine(int x1, int y1, int x2, int y2) {
	int   dx = x2 - x1, dy = y2 - y1;
	int   d2    = dx * dx + dy * dy;
	float d     = std::sqrt(d2);
	float stepX = dx / d, stepY = dy / d;

	for (int i = 0; i * i < d2; i++) {
	    drawPoint(x1 + (int)((i * stepX)), y1 + (int)(i * stepY),
	              255);
	}
    }

    template <class R>
    void Graphics<R>::drawBlob(int&& x, int&& y, int&& r, int&& color) {
	int dx = 0, dy = 0, d2 = (r * r);

	for (int i = x - r; i < x + r; i++) {
	    for (int j = y - r; j < y + r; j++) {
		dx = x - i;
		dy = y - j;
		if (dx * dx + dy * dy < d2) {
		    drawPoint(i, j, color);
		}
	    }
	}
    }

    template class gfx::Graphics<sdl::GLRenderer>;
    template class gfx::Graphics<sdl::SDLRenderer>;

}; // namespace gfx
