#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vk_renderer_world2d_frag_glsl_len = 205;
    const unsigned char Mapper::vk_renderer_world2d_frag_glsl[]   = {
#include "vk_renderer_world2d_frag_glsl_real.cxx"
    };
}; // namespace res
