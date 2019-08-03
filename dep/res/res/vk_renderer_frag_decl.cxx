#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vk_renderer_frag_len = 204;
    const unsigned char Mapper::vk_renderer_frag[]   = {
#include "vk_renderer_frag_real.cxx"
    };
}; // namespace res
