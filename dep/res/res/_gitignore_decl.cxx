#include "mapper.hpp"

namespace res {
    const size_t        Mapper::_gitignore_len = 42;
    const unsigned char Mapper::_gitignore[]   = {
#include "_gitignore_real.cxx"
    };
}; // namespace res
