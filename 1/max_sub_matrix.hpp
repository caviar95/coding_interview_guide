#pragma once

#include <vector>
#include <stack>

using namespace std;

enum SubMatrixType {
    ENUM,
    DP,
    STACK
};

class Solution {
public:
    int maxSubMatrix(const vector<vector<int>>& matrix, SubMatrixType type = ENUM) {
        if (type == ENUM) {
            return maxSubMatrix_enum(matrix);
        } else if (type == DP) {
            return maxSubMatrix_DP(matrix);
        } else if (type == STACK) {
            return maxSubMatrix_Monotonic(matrix);
        }

        return 0;
    }

private:
    // 暴力, O(m^3 * n^3) O(1)	极小规模数据验证          枚举所有可能的子矩阵，检查是否全为1，并计算最大面积。
    int maxSubMatrix_enum(const vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int maxArea{};

        int m = matrix.size();
        int n = matrix[0].size();

        // 枚举所有左上角 (i1, j1)
        for (int i1 = 0; i1 < m; ++i1) {
            for (int j1 = 0; j1 < n; ++j1) {
                if (matrix[i1][j1] == 0) {
                    continue;
                }

                int maxWidth = n;  // 当前行允许的最大宽度
                // 枚举右下角行 i2
                for (int i2 = i1; i2 < m; ++i2) {
                    if (matrix[i2][j1] == 0) {   // 列起始点非1则终止
                        break;
                    }
                    int curWidth = 0;
                    // 扩展当前行 j2 的宽度
                    for (int j2 = j1; j2 < maxWidth; ++j2) {
                        if (matrix[i2][j2] == 1) {
                            ++curWidth;
                        } else {
                            maxWidth = j2;  // 更新最大宽度限制
                            break;
                        }
                    }
                    maxArea = max(maxArea, (i2 - i1 + 1) * curWidth);
                }
            }
        }
        return maxArea;
    }

    // 动态规划, O(m^2 * n) O(mn)	中等规模数据 预处理每列连续1的高度，逐行扩展最大宽度。
    int maxSubMatrix_DP(const vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int maxArea{};

        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));  // 存储到当前行的最大宽度
    
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = (j == 0) ? 1 : dp[i][j-1] + 1;
                    int width = dp[i][j];
                    // 向上遍历行，计算最小宽度和高度
                    for (int k = i; k >= 0 && width > 0; --k) {
                        width = min(width, dp[k][j]);
                        maxArea = max(maxArea, width * (i - k + 1));
                    }
                }
            }
        }
        return maxArea;
    }



    // 单调栈 O(mn) O(n)	大规模高效计算         将每行视为柱状图，利用单调栈快速计算最大矩形。
    int maxSubMatrix_Monotonic(const vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int maxArea{};

        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);  // 存储每列的高度

        auto largestRectangleArea = [&]() -> int {
            stack<int> st;
            heights.push_back(0);  // 哨兵元素，确保栈清空
            int maxArea = 0;
            
            for (int i = 0; i < heights.size(); ++i) {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int h = heights[st.top()];
                    st.pop();
                    int w = st.empty() ? i : (i - st.top() - 1);
                    maxArea = max(maxArea, h * w);
                }
                st.push(i);
            }
            heights.pop_back();  // 恢复原数组
            return maxArea;
        };

        for (int i = 0; i < m; ++i) {
            // 更新当前行的高度
            for (int j = 0; j < n; ++j) {
                heights[j] = (matrix[i][j] == 1) ? heights[j] + 1 : 0;
            }
            // 计算当前行的最大矩形面积
            maxArea = max(maxArea, largestRectangleArea());
        }
        return maxArea;
    }
};

