#include "input.hpp"

namespace phx_sdl {

    template <typename Consumer = input::Simple>
    class Input {
    public:
	Input(input::Input<Consumer>& with) noexcept;

	// poll will block the current thread until quit is signaled.
	void poll() noexcept;

    private:
	input::Input<Consumer>& into;
    };

    template class Input<input::Simple>;

} // namespace phx_sdl