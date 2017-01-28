#ifndef LAMPORT_CLOCK_LAMPORT_CLOCK_H
#define LAMPORT_CLOCK_LAMPORT_CLOCK_H

#include <atomic>

class LamportClock {
public:
    /// Lamport timestamp
    typedef unsigned int LamportTime;

    LamportClock() : time_(0) {}

    /**
     * Get current Lamport timestamp.
     *
     * @return LamportTime value.
     */
    LamportTime get_time() const {
        return time_.load();
    }

    /**
     * Handle local event.
     * Increment timer and return the new value.
     *
     * @return LamportTime value;
     */
    LamportTime local_event() {
        return time_.fetch_add(1);
    }

    /**
     * Handle send event.
     * Increment local time and return the new value.
     *
     * @return LamportTime value;
     */
    LamportTime send_event() {
        return time_.fetch_add(1);
    }

    /**
     * Handle receive event.
     * Receive sender's time and set the local time to the maximum between received and local time plus 1.
     *
     * @param received_time Sender's time.
     * @return LamportTime value;
     */
    LamportTime receive_event(LamportTime received_time) {
        RECEIVE_EVENT:

        auto cur = get_time();

        // If received time is old, do nothing.
        if (received_time < cur) {
            return cur;
        }

        // Ensure that local timer is at least one ahead.
        if (!time_.compare_exchange_strong(cur, received_time + 1)) {
            goto RECEIVE_EVENT;
        }

        return received_time + 1;
    }

private:
    std::atomic<LamportTime> time_;
};

#endif //LAMPORT_CLOCK_LAMPORT_CLOCK_H
