#include "graphics.hpp"

/* WIP
namespace {
    template <typename R>
    constexpr void check_trait(decltype(Phoenix<R>) tp) {
        tp::gfxh::clear;
        tp::gfxh::update;
        tp::gfxh::draw;
    }

    template <typename R>
    constexpr void check_trait(decltype(Phoenix<R>) tp) {}
} // namespace

*/

template <typename R>
Phoenix<R>::Phoenix(gfx::Graphics<R>&& g) noexcept(false) : gfxh(g) {}

template <typename R>
void Phoenix<R>::render() noexcept(false) {
    gfxh.clear();
    gfxh.update();
    gfxh.draw();
}
