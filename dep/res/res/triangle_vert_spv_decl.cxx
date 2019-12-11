#include "mapper.hpp"

namespace res {
    const size_t        Mapper::triangle_vert_spv_len = 1468;
    const unsigned char Mapper::triangle_vert_spv[]   = {
#include "triangle_vert_spv_real.cxx"
    };
}; // namespace res
