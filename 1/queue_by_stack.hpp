#include <stack>

using namespace std;

class QueueByStack {
    stack<int> pushSt_;
    stack<int> popSt_;

    void push2pop() {
        if (popSt_.empty()) {
            while (!pushSt_.empty()) {
                popSt_.push(pushSt_.top());
                pushSt_.pop();
            }
        }
    }

public:
    QueueByStack() {}

    void push(int x) {
        pushSt_.push(x);
    }

    void pop() {
        if (pushSt_.empty() && popSt_.empty()) {
            return;
        }

        push2pop();

        popSt_.pop();
    }

    int peek() {
        if (pushSt_.empty() && popSt_.empty()) {
            return -1;
        }

        push2pop();

        return popSt_.top();
    }
};