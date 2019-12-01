#include "mapper.hpp"

namespace res {
    const size_t        Mapper::world2d_vert_spv_len = 1496;
    const unsigned char Mapper::world2d_vert_spv[]   = {
#include "world2d_vert_spv_real.cxx"
    };
}; // namespace res
