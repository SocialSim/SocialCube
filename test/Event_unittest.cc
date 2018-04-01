#include <cstdint>
#include "gtest/gtest.h"
#include "common/Event.hpp"

namespace {

const char* user_id = "YoyoWhatBringsYouHereBro";
const char* obj_id = "IWantToEncryptMyPasswordWithMD5";
const char* event_type = "Encrypt";
uint64_t ts = 2048;

TEST(EventTest, EventConstructor) {
    Event e(user_id, obj_id, event_type, ts);
    EXPECT_EQ(0, strcmp(e.getUserID().c_str(), user_id));
    EXPECT_EQ(0, strcmp(e.getObjectID().c_str(), obj_id));
    EXPECT_EQ(0, strcmp(e.getEventType().c_str(), event_type));
    EXPECT_EQ(e.getTimestamp(), ts);
}

}

