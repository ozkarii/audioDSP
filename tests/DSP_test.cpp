#include "gtest/gtest.h"
#include "DSP.hh"

TEST(DSPTest, zeroPadTest) {
    cVector a = {};
    cVector b = {0};
    cVector c = {0, {-2, 1}};
    cVector d = {{1, 2}, {3, -1}, {0, 0}, -9};
    cVector e = {3, -2, {1, 1}, 8, 10};

    cVector a1 = {0};
    cVector b1 = {0};
    cVector c1 = {{0, 0}, {-2, 1}};
    cVector d1 = {{1, 2}, {3, -1}, {0, 0}, {-9, 0}};
    cVector e1 = {{3, 0}, {-2, 0}, {1, 1}, {8, 0}, {10, 0}, {0, 0}, {0, 0}, {0, 0}};
    
    DSP::zeroPad(a);
    DSP::zeroPad(b);
    DSP::zeroPad(c);
    DSP::zeroPad(d);
    DSP::zeroPad(e);
    
    EXPECT_EQ(a, a1);
    EXPECT_EQ(b, b1);
    EXPECT_EQ(c, c1);
    EXPECT_EQ(d, d1);
    EXPECT_EQ(e, e1);
}