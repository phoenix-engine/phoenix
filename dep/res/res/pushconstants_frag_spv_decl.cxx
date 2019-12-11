#include "mapper.hpp"

namespace res {
    const size_t        Mapper::pushconstants_frag_spv_len = 1788;
    const unsigned char Mapper::pushconstants_frag_spv[]   = {
#include "pushconstants_frag_spv_real.cxx"
    };
}; // namespace res
