#include <gtest/gtest.h>
#include "../../include/lamport_clock.h"

TEST(LamportClock_Test, InitWithZero) {
    LamportClock clock;
    ASSERT_EQ(clock.get_time(), 0);
}

TEST(LamportClock_Test, LocalEvent) {
    LamportClock clock;
    clock.local_event();
    ASSERT_EQ(clock.get_time(), 1);
}

TEST(LamportClock_Test, SendEvent) {
    LamportClock clock;
    clock.send_event();
    ASSERT_EQ(clock.get_time(), 1);
}

TEST(LamportClock_Test, ReceiveEvent) {
    LamportClock clock;

    clock.receive_event(3);
    ASSERT_EQ(clock.get_time(), 4);

    clock.receive_event(2);
    ASSERT_EQ(clock.get_time(), 4);
}
