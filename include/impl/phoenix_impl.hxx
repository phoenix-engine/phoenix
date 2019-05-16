template <typename Consumer, typename Renderer, typename RenderPayload>
Phoenix<Consumer, Renderer, RenderPayload>::Phoenix(
  gfx::Graphics<Renderer, RenderPayload>&& g,
  input::Input<Consumer>&&                 input) noexcept(true)
    : gf(std::move(g)), in(std::move(input)) {}

template <typename Consumer, typename Renderer, typename RenderPayload>
void Phoenix<Consumer, Renderer, RenderPayload>::render(
  RenderPayload payload) noexcept(false) {
    gf.clear();
    gf.update();
    gf.draw(std::forward<RenderPayload>(payload));
}

template <typename Consumer, typename Renderer, typename RenderPayload>
input::Input<Consumer>&
Phoenix<Consumer, Renderer, RenderPayload>::input_handle() noexcept(
  true) {
    return in;
}
