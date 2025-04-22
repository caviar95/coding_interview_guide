#include <stack>

using namespace std;

// solution 1: less memory & more time
class MyStack1 {
    stack<int> data_;
    stack<int> min_;

public:
    MyStack1() {}

    void push(int newNum) {
        if (min_.empty() || newNum <= min_.top()) {
            min_.push(newNum);
        }

        data_.push(newNum);
    }

    int pop() {
        if (data_.empty()) {
            return -1; // 不使用异常
        }

        int value = data_.top();
        if (value == min_.top()) {
            min_.pop();
        }
        data_.pop();

        return value;
    }

    int getMin() {
        if (min_.empty()) {
            return -1; // 不使用异常
        }

        return min_.top();
    }
};

// solution 2: more memory & less time
class MyStack2 {
    stack<int> data_;
    stack<int> min_;
public:
    void push(int newNum) {
        if (min_.empty()) {
            min_.push(newNum);
        } else {
            min_.push(min_.top() < newNum ? min_.top() : newNum);
        }
        data_.push(newNum);
    }

    int pop() {
        if (data_.empty()) {
            return -1; // 不使用异常
        }

        min_.pop();
        int value = data_.top();
        data_.pop();
        return value;
    }

    int getMin() {
        if (min_.empty()) {
            return -1; // 不使用异常
        }

        return min_.top();
    }
};

