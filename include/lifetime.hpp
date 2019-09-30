#ifndef PHX_LIFETIME_HPP
#define PHX_LIFETIME_HPP

#include <memory>
#include <type_traits>

namespace phx {

    template <typename Resource, auto Destroyer>
    struct ResourceKeeper
        : public std::unique_ptr<Resource, decltype(Destroyer)> {

	static_assert(
	  std::is_invocable_v<decltype(Destroyer), Resource*>,
	  "Destroyer must be invocable on Resource*");

	ResourceKeeper(Resource* r) : unique_ptr(r, Destroyer) {}

	operator Resource*() const { return get(); }
    };

} // namespace phx

#endif // PHX_LIFETIME_HPP