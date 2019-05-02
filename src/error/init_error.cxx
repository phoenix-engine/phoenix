#include <sstream>
#include <string>

#include "init_error.hpp"

namespace phx_err {

    InitError::InitError() : exception() { msg.append(unknown); }

    InitError::InitError(std::string&& s)
        : exception(), msg(std::forward<std::string>(s)) {}

    InitError::InitError(std::stringstream& ss)
        : exception(), msg(ss.str()) {}

    const char* InitError::what() const noexcept { return msg.c_str(); }

} // namespace phx_err
