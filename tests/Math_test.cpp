#include "gtest/gtest.h"
#include "Math.hh"

TEST(MathTest, SincTest) {
    EXPECT_EQ(Math::sinc(0, 1), 1);
}
