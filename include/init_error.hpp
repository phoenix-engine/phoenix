#ifndef PHX_INIT_ERROR_H
#define PHX_INIT_ERROR_H

#include <exception>
#include <string>

namespace phx_err {

    class InitError : public std::exception {
    public:
	InitError();

	InitError(std::string&&);
	InitError(std::stringstream&);

	virtual const char* what() const noexcept;

    protected:
	std::string msg;

    private:
	constexpr const static std::string_view unknown =
	  "unknown error: ";
    };

} // namespace phx_err

#endif
