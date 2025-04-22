#include <gtest/gtest.h>
#include "queue_by_stack.hpp"

// 测试 QueueByStack 类的功能
class QueueByStackTest : public ::testing::Test {
protected:
    QueueByStack queue;
};

// 测试 push 和 peek 方法
TEST_F(QueueByStackTest, PushAndPeek) {
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.peek(), 1);
}

// 测试 push、pop 和 peek 方法的顺序行为
TEST_F(QueueByStackTest, PushPopPeekOrder) {
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.peek(), 1);
    queue.pop();
    EXPECT_EQ(queue.peek(), 2);
    queue.pop();
    EXPECT_EQ(queue.peek(), 3);
    queue.pop();

    // 队列为空，peek 应返回 -1
    EXPECT_EQ(queue.peek(), -1);
}

// 测试空队列的 pop 和 peek 行为
TEST_F(QueueByStackTest, EmptyQueue) {
    // 空队列，pop 不应改变队列状态
    queue.pop();

    // 空队列，peek 应返回 -1
    EXPECT_EQ(queue.peek(), -1);
}

// 测试多个元素的 push 和 pop 行为
TEST_F(QueueByStackTest, MultiplePushPop) {
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);

    queue.pop();
    queue.pop();

    EXPECT_EQ(queue.peek(), 3);
    queue.pop();
    EXPECT_EQ(queue.peek(), 4);
    queue.pop();

    // 队列再次为空，peek 应返回 -1
    EXPECT_EQ(queue.peek(), -1);
}
