template <class States>
const event::EventQueue& Input<States>::queue_handle() noexcept {
    return q;
}

template <class States>
void Input<States>::set_intent(int x0, int y0, bool intent0) {
    x = x0, y = y0;
    intent = intent0;
    next   = next->consume(this, q);
}

template <class States>
void Input<States>::move_intent(int x0, int y0) {
    x = x0, y = y0;
    next = next->consume(this, q);
}

template <class States>
void Input<States>::quit_command() {
    wants_quit = true;
    next       = next->consume(this, q);
}
