#pragma once

// implement a fifo with recursive func and stack
// return the bottom of stack, and remove it

#include <stack>
#include <optional>

using namespace std;

std::optional<int> getAndRemoveLastElement(stack<int> &st)
{
    if (st.empty()) {
        return nullopt;
    }

    int result = st.top();
    st.pop();

    if (st.empty()) {
        return result;
    }

    int last = getAndRemoveLastElement(st).value();
    st.push(result);

    return last;
}

void reverse(stack<int> &st)
{
    if (st.empty()) {
        return;
    }

    int last = getAndRemoveLastElement(st).value();
    reverse(st);
    st.push(last);
}