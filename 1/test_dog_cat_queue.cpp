#include "dog_cat_queue.hpp"
#include "gtest/gtest.h"

// 测试DogCatQueue类的添加和轮询功能
TEST(DogCatQueueTest, AddAndPoll) {
    DogCatQueue queue;

    // 添加一只狗和一只猫
    Dog dog("Buddy");
    Cat cat("Whiskers");
    queue.add(dog);
    queue.add(cat);

    // 轮询所有宠物，应该首先返回计数较小的那个（假设按添加顺序，这里应该是狗）
    Pet polledPet = queue.pollAll();
    EXPECT_EQ(polledPet.getPetType(), PetType::DOG);
    EXPECT_EQ(polledPet.getName(), "Buddy");

    // 再次轮询，应该返回猫
    polledPet = queue.pollAll();
    EXPECT_EQ(polledPet.getPetType(), PetType::CAT);
    EXPECT_EQ(polledPet.getName(), "Whiskers");

    // 队列现在应该为空
    EXPECT_TRUE(queue.isEmpty());
}

// 测试仅添加狗并轮询狗的功能
TEST(DogCatQueueTest, AddDogAndPollDog) {
    DogCatQueue queue;

    // 添加两只狗
    Dog dog1("Rex");
    Dog dog2("Fido");
    queue.add(dog1);
    queue.add(dog2);

    // 轮询狗，应该返回第一只添加的狗
    Dog polledDog = queue.pollDog();
    EXPECT_EQ(polledDog.getPetType(), PetType::DOG);
    EXPECT_EQ(polledDog.getName(), "Rex");

    // 再次轮询狗，应该返回第二只添加的狗
    polledDog = queue.pollDog();
    EXPECT_EQ(polledDog.getPetType(), PetType::DOG);
    EXPECT_EQ(polledDog.getName(), "Fido");

    // 狗队列现在应该为空
    EXPECT_TRUE(queue.isDogEmpty());
}

// 测试仅添加猫并轮询猫的功能
TEST(DogCatQueueTest, AddCatAndPollCat) {
    DogCatQueue queue;

    // 添加两只猫
    Cat cat1("Mittens");
    Cat cat2("Tom");
    queue.add(cat1);
    queue.add(cat2);

    // 轮询猫，应该返回第一只添加的猫
    Cat polledCat = queue.pollCat();
    EXPECT_EQ(polledCat.getPetType(), PetType::CAT);
    EXPECT_EQ(polledCat.getName(), "Mittens");

    // 再次轮询猫，应该返回第二只添加的猫
    polledCat = queue.pollCat();
    EXPECT_EQ(polledCat.getPetType(), PetType::CAT);
    EXPECT_EQ(polledCat.getName(), "Tom");

    // 猫队列现在应该为空
    EXPECT_TRUE(queue.isCatEmpty());
}
