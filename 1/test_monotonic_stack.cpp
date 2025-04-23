#include "monotonic_stack.hpp"
#include <gtest/gtest.h>

TEST(SmallerNumbers, Test1)
{
    vector<int> arr = {3, 4, 1, 5, 6, 2, 7};
    vector<pair<int, int>> expected{{-1, 2}, {0, 2}, {-1, -1}, {2, 5}, {3, 5}, {2, -1}, {5, -1}};
    EXPECT_EQ(smallerNumbers(arr), expected);
}
