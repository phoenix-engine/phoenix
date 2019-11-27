#include "mapper.hpp"

namespace res {
    const size_t        Mapper::triangle_frag_spv_len = 536;
    const unsigned char Mapper::triangle_frag_spv[]   = {
#include "triangle_frag_spv_real.cxx"
    };
}; // namespace res
