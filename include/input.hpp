#ifndef PHX_INPUT_INPUT_HPP
#define PHX_INPUT_INPUT_HPP

#include <type_traits>

#include "event.hpp"
#include "queue.hpp"

namespace input {

    namespace {
	using et = event::Event;
    }

    template <typename>
    class Consumer;

    class Simple;

    extern Simple simple;

    template <typename States = Simple>
    class Input {
    public:
	// Have to support trivial default constructor since Objective-C
	// frameworks require it.
	Input() noexcept(true)
	    : x(0), y(0), intent(false), wants_quit(false) {}
	Input(Consumer<States>* root) noexcept(true)
	    : x(0), y(0), intent(false), next(root), wants_quit(false) {
	}
	Input(Input&&) = default;
	// Input(Input&) = default;

	Input& operator=(Input&&) = default;

	void set_intent(int x, int y, bool intent);
	void move_intent(int x, int y);

	void quit_command();

	int  x, y;
	bool intent;

	friend States;

	event::EventQueue& queue_handle() noexcept;

    private:
	Consumer<States>* next;
	event::EventQueue q;

	bool wants_quit;
    };

    template <typename States = Simple>
    class Consumer {
    public:
	Consumer()          = default;
	Consumer(Consumer&) = delete;
	Consumer(States* f) noexcept : f(f) {}

	Consumer<States>* consume(Input<States>*    in,
	                          event::Queue<et>& eq) noexcept {
	    return f->consume(in, eq);
	}

    private:
	States* f;
    };

    class Simple : public Consumer<Simple> {
    public:
	Simple() noexcept
	    : Consumer(this), intent(false), box_begin({ 0, 0 }) {}
	Consumer<Simple>* consume(Input<Simple>*,
	                          event::Queue<et>&) noexcept;

    private:
	bool               intent;
	event::EventIntent box_begin;
    };

#include "impl/input_impl.hxx"

}; // namespace input

#endif // PHX_INPUT_INPUT_HPP
