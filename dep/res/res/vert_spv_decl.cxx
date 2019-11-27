#include "mapper.hpp"

namespace res {
    const size_t        Mapper::vert_spv_len = 1452;
    const unsigned char Mapper::vert_spv[]   = {
#include "vert_spv_real.cxx"
    };
}; // namespace res
