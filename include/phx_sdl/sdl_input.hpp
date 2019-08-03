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

    // Specialized only for input::Simple.  To enable further
    // specializations, add them to the implementation file.

} // namespace phx_sdl