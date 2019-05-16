#ifndef PHX_EVENT_QUEUE_HPP
#define PHX_EVENT_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

namespace event {

    template <typename Evt>
    class Queue {
    public:
	Queue() = default;
	Queue(Queue& qq) noexcept : m(), cv() {
	    // Lock before cloning the queue.
	    std::unique_lock<std::mutex> lock(qq.m);
	    q = qq.q;
	}

	Queue(Queue&& qq) noexcept : m(), cv() {
	    std::unique_lock<std::mutex> lock(qq.m);
	    q = std::move(qq.q);
	}

	Queue& operator=(Queue&& qq) noexcept {
	    std::scoped_lock<std::mutex, std::mutex> lock(m, qq.m);
	    q = std::move(qq.q);
	    return *this;
	}

	bool enqueue(Evt e) noexcept {
	    std::unique_lock<std::mutex> lock(m);

	    q.emplace(e);
	    cv.notify_one();

	    return true;
	}

	Evt await() noexcept {
	    std::unique_lock<std::mutex> lock(m);
	    if (q.size() == 0) {
		// Block the current thread and unlock the mutex until
		// something arrives.  Then awaken, lock, and continue.
		cv.wait(lock, [&] { return q.size() > 0; });
	    }

	    auto e = q.front();
	    q.pop();

	    return e;
	}

    private:
	std::mutex              m;
	std::condition_variable cv;
	std::queue<Evt>         q;
    };

    typedef Queue<Event> EventQueue;

}; // namespace event

#endif // PHX_EVENT_QUEUE_HPP
