#include "my_math.hpp"

#include <gtest/gtest.h>

TEST(Math, Add)
    {
        EXPECT_EQ(add(10,20), 30);
        EXPECT_EQ(add(4,5), 9);
    }
TEST(Math, Multiply)
    {
        EXPECT_EQ(multiply(10,20), 200);
        EXPECT_EQ(multiply(4,5), 20);
    }