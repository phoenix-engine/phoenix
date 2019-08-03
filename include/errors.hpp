#ifndef PHX_ERRORS_HPP
#define PHX_ERRORS_HPP

#include <exception>
#include <string_view>

namespace phx_err {

    namespace {
	const static std::string_view retry_what = "phx_err::Retry";
    }

    struct Retry : public std::exception {
    public:
	virtual char const* what() const override {
	    return retry_what.data();
	}

    private:
    };

} // namespace phx_err

#endif // PHX_ERRORS_HPP