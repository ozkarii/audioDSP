#include "gtest/gtest.h"
#include "Math.hh"

TEST(MathTest, sincTest) {
    EXPECT_EQ(Math::sinc(0, 1), 1);
    EXPECT_LT(Math::sinc(M_PI), 1e-14);
}

TEST(MathTest, multiplyElementWiseTest) {
    cVector a = {-2, -1.1, 0, 1, 2.232};
    cVector b = {30, 2, 3.1, 1232.1, 2.0};
    cVector c = {-60, -2.2, 0, 1232.1, 4.464};
    std::vector<double> d = {-2, -1.1, 0, 1, 2.232};
    std::vector<double> e = {30, 2, 3.1, 1232.1, 2.0};
    std::vector<double> f = {-60, -2.2, 0, 1232.1, 4.464};
    EXPECT_EQ(Math::multiplyElementWise(a, b), c);
    EXPECT_EQ(Math::multiplyElementWise(d, e), f);
}