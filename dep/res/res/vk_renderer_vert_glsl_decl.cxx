#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vk_renderer_vert_glsl_len = 419;
    const unsigned char Mapper::vk_renderer_vert_glsl[]   = {
#include "vk_renderer_vert_glsl_real.cxx"
    };
}; // namespace res
