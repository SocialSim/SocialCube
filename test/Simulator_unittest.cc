#include "gtest/gtest.h"
#include "Simulator/Simulator.hpp"

namespace {

TEST(SimulatorTest, BasicTimeSetting) {
    Simulator s;
    s.setCurrentTime(1024);
    EXPECT_EQ(s.getCurrentTime(), 1024);
}

}

