#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vk_renderer_vert_len = 436;
    const unsigned char Mapper::vk_renderer_vert[]   = {
#include "vk_renderer_vert_real.cxx"
    };
}; // namespace res
