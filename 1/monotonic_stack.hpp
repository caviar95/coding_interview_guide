#pragma once

/*
    找出每一个i左侧和右侧比自己小的元素对
*/

#include <stack>
#include <vector>

using namespace std;

vector<pair<int, int>> smallerNumbers(vector<int>& nums)
{
    int n = nums.size();

    vector<int> pre(n, -1);
    vector<int> suf(n, -1);

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && nums[i] < nums[st.top()]) {
            suf[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    st = {};
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && nums[i] < nums[st.top()]) {
            pre[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    vector<pair<int, int>> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = {pre[i], suf[i]};
    }

    return ans;
}