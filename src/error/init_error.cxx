#include <iterator>
#include <string>

#include "init_error.hpp"

namespace phx_err {

    InitError::InitError() : InitError(unknown.data()) {}

    InitError::InitError(std::string&& s)
        : exception(), message(std::move(s)) {}

    InitError::InitError(std::stringstream& ss) : InitError(ss.str()) {}

    char const* InitError::what() const { return message.c_str(); }

} // namespace phx_err
