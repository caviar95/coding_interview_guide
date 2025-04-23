#include <vector>
#include "gtest/gtest.h"
#include "max_val_sliding_window.hpp"

using namespace std;

TEST(SlidingWindowTest, BasicWindowOperation) {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> expected = {3, 3, 5, 5, 6, 7};
    EXPECT_EQ(getMaxWindow(nums, 3), expected);
}

TEST(SlidingWindowTest, DecreasingSequence) {
    vector<int> nums = {5, 4, 3, 2, 1};
    vector<int> expected = {5, 4, 3};
    EXPECT_EQ(getMaxWindow(nums, 3), expected);
}

TEST(SlidingWindowTest, WindowSizeOne) {
    vector<int> nums = {2, 1, 5, 3, 4};
    vector<int> expected = {2, 1, 5, 3, 4};
    EXPECT_EQ(getMaxWindow(nums, 1), expected);
}

TEST(SlidingWindowTest, FullArrayWindow) {
    vector<int> nums = {7, 2, 4, 1, 5};
    vector<int> expected = {7};
    EXPECT_EQ(getMaxWindow(nums, 5), expected);
}

TEST(SlidingWindowTest, DuplicateValues) {
    vector<int> nums = {2, 2, 2, 2, 2};
    vector<int> expected = {2, 2, 2};
    EXPECT_EQ(getMaxWindow(nums, 3), expected);
}

TEST(SlidingWindowTest, EmptyInput) {
    vector<int> nums;
    vector<int> expected;
    EXPECT_EQ(getMaxWindow(nums, 3), expected);
}

TEST(SlidingWindowTest, InvalidWindowSize) {
    vector<int> nums = {1, 2, 3};
    vector<int> expected;
    EXPECT_EQ(getMaxWindow(nums, 0), expected);  // 零窗口
    EXPECT_EQ(getMaxWindow(nums, -2), expected); // 负数窗口
}

TEST(SlidingWindowTest, WindowLargerThanArray) {
    vector<int> nums = {1, 2, 3};
    vector<int> expected;
    EXPECT_EQ(getMaxWindow(nums, 5), expected);
}

TEST(SlidingWindowTest, RandomSequence) {
    vector<int> nums = {4, 2, 5, 3, 7, 1, 6};
    vector<int> expected = {5, 7, 7, 7};
    EXPECT_EQ(getMaxWindow(nums, 4), expected);
}

TEST(SlidingWindowTest, AscendingOrder) {
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> expected = {3, 4, 5};
    EXPECT_EQ(getMaxWindow(nums, 3), expected);
}