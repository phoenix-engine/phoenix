#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vk_renderer_triangle_vert_glsl_len = 429;
    const unsigned char Mapper::vk_renderer_triangle_vert_glsl[]   = {
#include "vk_renderer_triangle_vert_glsl_real.cxx"
    };
}; // namespace res
