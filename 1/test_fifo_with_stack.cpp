#include <gtest/gtest.h>
#include <stack>
#include "fifo_with_stack.hpp"

// 辅助函数，用于比较两个栈是否相等
bool stacksAreEqual(const stack<int>& st1, const stack<int>& st2) {
    stack<int> temp1 = st1;
    stack<int> temp2 = st2;

    while (!temp1.empty() && !temp2.empty()) {
        if (temp1.top() != temp2.top()) {
            return false;
        }
        temp1.pop();
        temp2.pop();
    }

    return temp1.empty() && temp2.empty();
}

// 测试 getAndRemoveLastElement 函数
TEST(FifoWithStackTest, GetAndRemoveLastElement) {
    stack<int> st;

    // 测试空栈情况
    auto result = getAndRemoveLastElement(st);
    EXPECT_FALSE(result.has_value()); // 期望返回 nullopt

    // 测试单元素栈
    st.push(2);
    result = getAndRemoveLastElement(st);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 2);
    EXPECT_TRUE(st.empty());

    // 测试多元素栈
    st.push(1);
    st.push(2);
    st.push(3);
    result = getAndRemoveLastElement(st);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 1);
    EXPECT_EQ(st.top(), 3);
    st.pop();
    EXPECT_EQ(st.top(), 2);
    st.pop();

    EXPECT_TRUE(st.empty());
}

// 测试 reverse 函数
TEST(FifoWithStackTest, Reverse) {
    stack<int> st;

    // 测试空栈情况
    reverse(st);
    EXPECT_TRUE(st.empty());

    // 测试单元素栈
    st.push(1);
    reverse(st);
    EXPECT_EQ(st.top(), 1);
    st.pop();
    EXPECT_TRUE(st.empty());

    // 测试多元素栈
    st.push(1);
    st.push(2);
    st.push(3);
    reverse(st);
    EXPECT_EQ(st.top(), 1);
    st.pop();
    EXPECT_EQ(st.top(), 2);
    st.pop();
    EXPECT_EQ(st.top(), 3);
    st.pop();
    EXPECT_TRUE(st.empty());

    // 测试包含重复元素的栈
    st.push(1);
    st.push(2);
    st.push(2);
    st.push(1);
    reverse(st);
    stack<int> expected;
    expected.push(1);
    expected.push(2);
    expected.push(2);
    expected.push(1);
    EXPECT_TRUE(stacksAreEqual(st, expected));
}
