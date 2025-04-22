#include <gtest/gtest.h>
#include "get_min.hpp" // 假设 get_min.cpp 在同一目录下

// 测试 MyStack1 类
TEST(MyStack1Test, PushAndPop) {
    MyStack1 stack;
    stack.push(5);
    stack.push(3);
    stack.push(7);
    EXPECT_EQ(stack.pop(), 7);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 5);
}

TEST(MyStack1Test, GetMin) {
    MyStack1 stack;
    stack.push(5);
    stack.push(3);
    stack.push(7);
    EXPECT_EQ(stack.getMin(), 3);
    stack.pop();
    EXPECT_EQ(stack.getMin(), 3);
    stack.pop();
    EXPECT_EQ(stack.getMin(), 5);
}

TEST(MyStack1Test, EmptyStack) {
    MyStack1 stack;
    EXPECT_EQ(stack.pop(), -1);
    EXPECT_EQ(stack.getMin(), -1);
}

// 测试 MyStack2 类
TEST(MyStack2Test, PushAndPop) {
    MyStack2 stack;
    stack.push(5);
    stack.push(3);
    stack.push(7);
    EXPECT_EQ(stack.pop(), 7);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 5);
}

TEST(MyStack2Test, GetMin) {
    MyStack2 stack;
    stack.push(5);
    stack.push(3);
    stack.push(7);
    EXPECT_EQ(stack.getMin(), 3);
    stack.pop();
    EXPECT_EQ(stack.getMin(), 3);
    stack.pop();
    EXPECT_EQ(stack.getMin(), 5);
}

TEST(MyStack2Test, EmptyStack) {
    MyStack2 stack;
    EXPECT_EQ(stack.pop(), -1);
    EXPECT_EQ(stack.getMin(), -1);
}
