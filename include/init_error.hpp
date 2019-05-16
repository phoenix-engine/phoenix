#ifndef PHX_INIT_ERROR_H
#define PHX_INIT_ERROR_H

#include <exception>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

namespace phx_err {

    namespace {
	const static std::string_view unknown = "unknown error";
    };

    class InitError : public std::exception {
    public:
	InitError();

	InitError(std::string&&);
	InitError(std::stringstream&);

	virtual char const* what() const override;

    protected:
	std::string message;
    };

} // namespace phx_err

#endif
