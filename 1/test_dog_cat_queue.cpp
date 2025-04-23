#include "dog_cat_queue.hpp"
#include "gtest/gtest.h"

/*
    关键测试点说明：
        基础功能测试：验证队列的基本添加/出队操作和状态跟踪
        类型特定操作：独立测试狗和猫队列的出队功能
        时间戳顺序：确保混合类型按入队顺序出队
        异常安全：覆盖所有异常抛出场景
        移动语义：验证资源正确转移（需结合内存检查工具）
        状态转换：测试队列状态机的各种转换路径
        混合操作：模拟复杂使用场景

    执行测试时需要链接Google Test库，建议使用现代C++编译选项（C++17或更高）。测试覆盖率应达到：
        100% 代码行覆盖
        所有分支条件覆盖
        所有异常路径覆盖
        边界条件全覆盖
*/

TEST(DogCatQueueTest, BasicEnqueueDequeue) {
    DogCatQueue q;
    
    // 验证空队列状态
    EXPECT_TRUE(q.empty());
    EXPECT_TRUE(q.dogs_empty());
    EXPECT_TRUE(q.cats_empty());
    
    // 添加宠物
    q.add(Pet(PetType::DOG, "Buddy"));
    q.add(Pet(PetType::CAT, "Whiskers"));
    
    // 验证非空状态
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.dogs_empty());
    EXPECT_FALSE(q.cats_empty());
    
    // 验证出队顺序
    auto first = q.poll();
    EXPECT_EQ(first.type(), PetType::DOG);
    EXPECT_EQ(first.name(), "Buddy");
    
    auto second = q.poll();
    EXPECT_EQ(second.type(), PetType::CAT);
    EXPECT_EQ(second.name(), "Whiskers");
}

TEST(DogCatQueueTest, TypeSpecificDequeue) {
    DogCatQueue q;
    
    q.add(Pet(PetType::DOG, "Rex"));
    q.add(Pet(PetType::CAT, "Tom"));
    q.add(Pet(PetType::DOG, "Fido"));
    
    // 单独出队狗
    auto dog1 = q.poll_dog();
    EXPECT_EQ(dog1.name(), "Rex");
    
    // 单独出队猫
    auto cat = q.poll_cat();
    EXPECT_EQ(cat.name(), "Tom");
    
    // 混合出队
    auto dog2 = q.poll();
    EXPECT_EQ(dog2.name(), "Fido");
}

TEST(DogCatQueueTest, TimestampOrdering) {
    DogCatQueue q;
    
    // 验证时间戳顺序
    q.add(Pet(PetType::CAT, "C1"));
    q.add(Pet(PetType::DOG, "D1"));
    q.add(Pet(PetType::CAT, "C2"));
    
    EXPECT_EQ(q.poll().name(), "C1");  // 最早入队
    EXPECT_EQ(q.poll().name(), "D1");
    EXPECT_EQ(q.poll().name(), "C2");
}

TEST(DogCatQueueTest, ExceptionHandling) {
    DogCatQueue q;
    
    // 空队列异常
    EXPECT_THROW(q.poll(), std::runtime_error);
    EXPECT_THROW(q.poll_dog(), std::runtime_error);
    EXPECT_THROW(q.poll_cat(), std::runtime_error);
    
    // 无效类型异常
    Pet invalid_pet(static_cast<PetType>(2), "Unknown");
    EXPECT_THROW(q.add(std::move(invalid_pet)), std::invalid_argument);
}

TEST(DogCatQueueTest, MoveSemantics) {
    DogCatQueue q;
    
    // 验证移动语义
    Pet dog(PetType::DOG, "Rover");
    q.add(std::move(dog));
    
    // 原始对象不应再被使用（这里只是演示测试方法）
    // 实际使用中应避免访问已移动对象
    
    auto dequeued = q.poll_dog();
    EXPECT_EQ(dequeued.name(), "Rover");
}

TEST(DogCatQueueTest, MixedOperations) {
    DogCatQueue q;
    
    // 复杂操作序列
    q.add(Pet(PetType::DOG, "D1"));
    q.add(Pet(PetType::CAT, "C1"));
    q.add(Pet(PetType::CAT, "C2"));
    
    EXPECT_EQ(q.poll_cat().name(), "C1");
    EXPECT_EQ(q.poll().name(), "D1");  // 最早剩余元素
    
    q.add(Pet(PetType::DOG, "D2"));
    EXPECT_EQ(q.poll().name(), "C2");  // 时间戳早于D2
}

TEST(DogCatQueueTest, StateTransitions) {
    DogCatQueue q;
    
    // 初始状态验证
    EXPECT_TRUE(q.empty());
    
    // 添加狗
    q.add(Pet(PetType::DOG, "Buddy"));
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.dogs_empty());
    EXPECT_TRUE(q.cats_empty());
    
    // 添加猫
    q.add(Pet(PetType::CAT, "Mittens"));
    EXPECT_FALSE(q.cats_empty());
    
    // 清空狗队列
    q.poll_dog();
    EXPECT_TRUE(q.dogs_empty());
    EXPECT_FALSE(q.empty());
    
    // 清空猫队列
    q.poll_cat();
    EXPECT_TRUE(q.empty());
}

#if 0
/*
    增加参数化测试
*/

// 参数化测试数据结构
struct QueueTestParams {
    PetType pet_type;
    std::string first_name;
    std::string second_name;
    std::string third_name;
};

// 基础功能参数化测试
class BasicQueueTest : public testing::TestWithParam<QueueTestParams> {
protected:
    DogCatQueue queue;
};

TEST_P(BasicQueueTest, AddAndPoll) {
    const auto& params = GetParam();
    
    // 添加三个同类型宠物
    queue.add(Pet(params.pet_type, params.first_name));
    queue.add(Pet(params.pet_type, params.second_name));
    queue.add(Pet(params.pet_type, params.third_name));

    // 验证按顺序出队
    EXPECT_EQ(queue.poll().name(), params.first_name);
    EXPECT_EQ(queue.poll().name(), params.second_name);
    EXPECT_EQ(queue.poll().name(), params.third_name);
}

INSTANTIATE_TEST_SUITE_P(
    PetTypeTests,
    BasicQueueTest,
    testing::Values(
        QueueTestParams{PetType::DOG, "Buddy", "Rex", "Fido"},
        QueueTestParams{PetType::CAT, "Whiskers", "Mittens", "Tom"}
    )
);

// 混合队列参数化测试
class MixedQueueTest : public testing::TestWithParam<std::tuple<
    std::vector<std::pair<PetType, std::string>>,  // 输入序列
    std::vector<std::string>                       // 期望输出
    >> {};

TEST_P(MixedQueueTest, VerifyPollOrder) {
    auto [input, expected] = GetParam();
    DogCatQueue queue;

    // 按输入序列添加宠物
    for (const auto& [type, name] : input) {
        queue.add(Pet(type, name));
    }

    // 验证出队顺序
    for (const auto& expected_name : expected) {
        EXPECT_EQ(queue.poll().name(), expected_name);
    }
}

INSTANTIATE_TEST_SUITE_P(
    SequenceTests,
    MixedQueueTest,
    testing::Values(
        // 测试用例1：交替添加
        std::make_tuple(
            std::vector{
                std::pair{PetType::DOG, "D1"},
                std::pair{PetType::CAT, "C1"},
                std::pair{PetType::DOG, "D2"}
            },
            std::vector{"D1", "C1", "D2"}
        ),
        // 测试用例2：猫先出队
        std::make_tuple(
            std::vector{
                std::pair{PetType::CAT, "C1"},
                std::pair{PetType::DOG, "D1"},
                std::pair{PetType::CAT, "C2"}
            },
            std::vector{"C1", "D1", "C2"}
        )
    )
);

// 保留原有的异常测试等非参数化测试
TEST(DogCatQueueTest, ExceptionHandling) {
    DogCatQueue q;
    EXPECT_THROW(q.poll(), std::runtime_error);
    EXPECT_THROW(q.poll_dog(), std::runtime_error);
    EXPECT_THROW(q.poll_cat(), std::runtime_error);
}
#endif
