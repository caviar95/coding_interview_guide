#pragma once

#include <string>
#include <queue>
#include <stdexcept>
#include <utility>
#include <cstdint>

enum class PetType { DOG, CAT };

class Pet {
    PetType type_;
    std::string name_;
    
public:
    Pet(PetType type, std::string name) 
        : type_(type), name_(std::move(name)) {}
    
    PetType type() const noexcept { return type_; }
    const std::string& name() const noexcept { return name_; }

    // 支持移动语义
    Pet(Pet&&) = default;
    Pet& operator=(Pet&&) = default;
    
    // 禁用拷贝（根据需要开放）
    Pet(const Pet&) = delete;
    Pet& operator=(const Pet&) = delete;
};

class TimestampPet {
    Pet pet_;
    uint64_t timestamp_;
    
public:
    TimestampPet(Pet&& pet, uint64_t ts)
        : pet_(std::move(pet)), timestamp_(ts) {}
    
    uint64_t timestamp() const noexcept { return timestamp_; }
    const Pet& pet() const noexcept { return pet_; }
    PetType type() const noexcept { return pet_.type(); }
};

class DogCatQueue {
    std::queue<TimestampPet> dogs_;
    std::queue<TimestampPet> cats_;
    uint64_t counter_ = 0;
    
    // 通用出队模板
    template <PetType T>
    Pet poll_impl(std::queue<TimestampPet>& q) {
        if (q.empty()) throw std::runtime_error("Queue empty");
        
        auto entry = std::move(q.front());
        q.pop();
        return std::move(const_cast<Pet&>(entry.pet()));
    }

public:
    void add(Pet&& pet) {
        switch (pet.type()) {
        case PetType::DOG:
            dogs_.emplace(std::move(pet), counter_++);
            break;
        case PetType::CAT:
            cats_.emplace(std::move(pet), counter_++);
            break;
        default:
            throw std::invalid_argument("Invalid pet type");
        }
    }

    // 统一出队接口
    Pet poll() {
        if (empty()) throw std::runtime_error("All queues empty");
        
        const auto dog_ts = dogs_.empty() ? UINT64_MAX : dogs_.front().timestamp();
        const auto cat_ts = cats_.empty() ? UINT64_MAX : cats_.front().timestamp();
        
        return dog_ts < cat_ts ? poll_dog() : poll_cat();
    }

    Pet poll_dog() { return poll_impl<PetType::DOG>(dogs_); }
    Pet poll_cat() { return poll_impl<PetType::CAT>(cats_); }

    // 状态查询（添加noexcept）
    bool empty() const noexcept { return dogs_.empty() && cats_.empty(); }
    bool dogs_empty() const noexcept { return dogs_.empty(); }
    bool cats_empty() const noexcept { return cats_.empty(); }
};