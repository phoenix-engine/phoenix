template <typename Consumer, typename Renderer, typename RenderPayload>
Phoenix<Consumer, Renderer, RenderPayload>::Phoenix(
  gfx::Graphics<Renderer, RenderPayload>&& g,
  input::Input<Consumer>&&                 input) noexcept(true)
    : gf(std::move(g)), in(std::move(input)) {}

template <typename Consumer, typename Renderer, typename RenderPayload>
void Phoenix<Consumer, Renderer, RenderPayload>::update(
  const event::EventIntent& in) noexcept(false) {
    gf.update(in);
}

template <typename Consumer, typename Renderer, typename RenderPayload>
void Phoenix<Consumer, Renderer, RenderPayload>::render(
  RenderPayload payload) noexcept(false) {
    gf.clear();
    gf.draw(std::forward<RenderPayload>(payload));
}

template <typename Consumer, typename Renderer, typename RenderPayload>
input::Input<Consumer>&
Phoenix<Consumer, Renderer, RenderPayload>::input_handle() noexcept(
  true) {
    return in;
}

template <typename Consumer, typename Renderer, typename RenderPayload>
typename Phoenix<Consumer, Renderer, RenderPayload>::Metrics
Phoenix<Consumer, Renderer, RenderPayload>::get_metrics() noexcept(
  true) {
    return typename Phoenix<Consumer, Renderer, RenderPayload>::Metrics{
	gf.get_metrics()
    };
}
