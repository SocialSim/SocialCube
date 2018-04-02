#include <cstdint>
#include "gtest/gtest.h"
#include "Dependency/ObjectPreference.hpp"

namespace {

TEST(ObjectPreferenceTest, RandomChooseTargetTest) {
    ObjectPreference op("Vader");
    op.set("LukeSkyWalker", 0.1);
    op.set("Yoda", 0.3);
    op.set("3PO", 0.5);
    op.set("Obi-Wan", 0.7);
    op.set("Chewbacca", 0.9);
    op.set("HanSolo", 1.0);
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.2).c_str(), "Yoda"));
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.05).c_str(), "LukeSkyWalker"));
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.45).c_str(), "3PO"));
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.6).c_str(), "Obi-Wan"));
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.8).c_str(), "Chewbacca"));
    EXPECT_EQ(0, strcmp(op.randomChooseTarget(true, 0.99).c_str(), "HanSolo"));
}

}

