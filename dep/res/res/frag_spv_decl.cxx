#include "mapper.hpp"

namespace res {
    const size_t        Mapper::frag_spv_len = 536;
    const unsigned char Mapper::frag_spv[]   = {
#include "frag_spv_real.cxx"
    };
}; // namespace res
