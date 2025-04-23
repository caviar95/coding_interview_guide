#include "dog_cat_queue.hpp"
#include "gtest/gtest.h"

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