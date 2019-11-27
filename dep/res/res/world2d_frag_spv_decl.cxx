#include "mapper.hpp"

namespace res {
    const size_t        Mapper::world2d_frag_spv_len = 536;
    const unsigned char Mapper::world2d_frag_spv[]   = {
#include "world2d_frag_spv_real.cxx"
    };
}; // namespace res
