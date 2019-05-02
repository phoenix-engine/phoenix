template <typename Renderer, typename RenderPayload>
Graphics<Renderer, RenderPayload>::Graphics(Renderer&& r, int wIn,
                                            int hIn) noexcept(true)
    : w(wIn), h(hIn), renderer(r) {}

template <typename Renderer, typename RenderPayload>
void Graphics<Renderer, RenderPayload>::update() {
    renderer.update();
}

template <typename Renderer, typename RenderPayload>
void Graphics<Renderer, RenderPayload>::draw(RenderPayload& payload) {
    renderer.draw(payload);
}

template <typename Renderer, typename RenderPayload>
void Graphics<Renderer, RenderPayload>::clear() {
    renderer.clear();
}

template <typename Renderer, typename RenderPayload>
void Graphics<Renderer, RenderPayload>::drawLine(int x1, int y1, int x2,
                                                 int y2) {
    int   dx = x2 - x1, dy = y2 - y1;
    int   d2    = dx * dx + dy * dy;
    float d     = std::sqrt(d2);
    float stepX = dx / d, stepY = dy / d;

    for (int i = 0; i * i < d2; i++) {
	drawPoint(x1 + (int)((i * stepX)), y1 + (int)(i * stepY), 255);
    }
}

template <typename Renderer, typename RenderPayload>
void Graphics<Renderer, RenderPayload>::drawBlob(int x, int y, int r,
                                                 int color) {
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
