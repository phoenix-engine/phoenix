#include "mapper.hpp"

namespace res {
    const size_t        Mapper::pushconstants_vert_spv_len = 1632;
    const unsigned char Mapper::pushconstants_vert_spv[]   = {
#include "pushconstants_vert_spv_real.cxx"
    };
}; // namespace res
