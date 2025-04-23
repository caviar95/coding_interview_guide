#pragma once

#include <string>
#include <queue>

using namespace std;

enum class PetType {DEFAULT, DOG, CAT};
class Pet {
    PetType type;
    string name;

public:
    Pet(PetType t = PetType::DEFAULT, const string &petName = "") : type(t), name(petName) {}

    Pet(const Pet &pet) {
        type = pet.type;
        name = pet.name;
    }

    PetType getPetType() const {
        return type;
    }

    string getName() const {
        return name;
    }
};

class Dog : public Pet {
public:
    Dog(const string &name = "") : Pet(PetType::DOG, name) {}
};

class Cat : public Pet {
public:
    Cat(const string &name = "") : Pet(PetType::CAT, name) {}
};

class PetEnterQueue {
    Pet pet;
    long count;

public:
    PetEnterQueue(Pet pet, long cnt) : pet(pet), count(cnt) {}

    long getCount() const {
        return count;
    }

    Pet getPet() const {
        return pet;
    }

    PetType getPetType() const {
        return pet.getPetType();
    }
};

class DogCatQueue {
    queue<PetEnterQueue> dogQ_;
    queue<PetEnterQueue> catQ_;
    long count_{};

public:
    DogCatQueue() {}

    void add(const Pet &pet) {
        if (pet.getPetType() == PetType::DOG) {
            dogQ_.push(PetEnterQueue(pet, count_++));
        } else if (pet.getPetType() == PetType::CAT) {
            catQ_.push(PetEnterQueue(pet, count_++));
        }
    }

    Pet pollAll() {
        if (!dogQ_.empty() && !catQ_.empty()) {
            if (dogQ_.front().getCount() < catQ_.front().getCount()) {
                auto pet = dogQ_.front().getPet();
                dogQ_.pop();
                return pet;
            }
            auto pet = catQ_.front().getPet();
            catQ_.pop();
            return pet;    
        }

        if (!dogQ_.empty()) {
            auto pet = dogQ_.front().getPet();
            dogQ_.pop();
            return pet;
        }

        if (!catQ_.empty()) {
            auto pet = catQ_.front().getPet();
            catQ_.pop();
            return pet;  
        }

        return {};
    }

    Dog pollDog() {
        if (!dogQ_.empty()) {
            auto pet = dogQ_.front().getPet();
            Dog dog(pet.getName());
            dogQ_.pop();
            return dog;
        }

        return {};
    }

    Cat pollCat() {
        if (!catQ_.empty()) {
            auto pet = catQ_.front().getPet();
            Cat cat(pet.getName());
            catQ_.pop();
            return cat;
        }

        return {};
    }

    bool isEmpty() {
        return dogQ_.empty() && catQ_.empty();
    }

    bool isDogEmpty() {
        return dogQ_.empty();
    }

    bool isCatEmpty() {
        return catQ_.empty();
    }
};
