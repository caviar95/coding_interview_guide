#pragma once

#include <vector>
#include <queue>

using namespace std;

vector<int> getMaxWindow(const vector<int>& nums, int width)
{
    if (nums.empty() || width <= 0 || nums.size() < width) {
        return {};
    }

    deque<pair<int, int>> dq;
    vector<int> result;

    for (int i = 0; i < nums.size(); ++i) {
        while (!dq.empty() && nums[i] > dq.back().first) {
            dq.pop_back();
        }

        dq.emplace_back(nums[i], i);

        if (i - dq.front().second >= width) {
            dq.pop_front();
        }

        if (i >= width - 1) {
            result.push_back(dq.front().first);
        }
    }

    return result;
}
