//
//  Renderer_impl.hxx
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 2/16/19.
//

#ifndef PHX_MTLP_Renderer_impl_hxx
#define PHX_MTLP_Renderer_impl_hxx

template <typename InternalRenderer, typename RenderPayload>
Renderer<InternalRenderer, RenderPayload>::Renderer(InternalRenderer& pr) : r(pr) {};

template <typename InternalRenderer, typename RenderPayload>
void Renderer<InternalRenderer, RenderPayload>::postHooks() noexcept(true) {
    [InternalRenderer postHooks];
};

template <typename InternalRenderer, typename RenderPayload>
void Renderer<InternalRenderer, RenderPayload>::update() { [r update]; }

template <typename InternalRenderer, typename RenderPayload>
void draw_on(InternalRenderer& r, RenderPayload& pl) {
    // TODO: Make this less terrible.  At least it works.  Really what I want is
    // an optional payload type parameter.
    [r draw: pl];
}

template <typename InternalRenderer, typename RenderPayload>
void Renderer<InternalRenderer, RenderPayload>::draw(RenderPayload& pl) {
    [r draw: pl];
}

template <typename InternalRenderer, typename RenderPayload>
void Renderer<InternalRenderer, RenderPayload>::clear() { [r clear]; }

template <typename InternalRenderer, typename RenderPayload>
void Renderer<InternalRenderer, RenderPayload>::drawPoint(int x, int y, int color) {

    double red = static_cast<double>((color & 0xFF000000) >> 6),
        green = static_cast<double>((color & 0x00FF0000) >> 4),
        blue = static_cast<double>((color & 0x0000FF00) >> 2),
        alpha = static_cast<double>(color & 0x000000FF);

    [r drawPointAt:simd_int2{x, y}
         withColor:MTLClearColorMake(red, green, blue, alpha)];
}

#endif /* PHX_MTLP_Renderer_impl_hxx */
