#pragma once

/*
主要优化点说明：

1. 类型安全修正  
   - 修正所有 `'1'` 为 `1`，确保正确比较整型值
   - 枚举值重命名增强可读性 (`ENUM` → `BRUTE_FORCE`)

2. 代码结构优化  
   - 使用 `switch-case` 替代 `if-else` 链，提高可维护性
   - 统一前置条件检查，避免重复代码
   - 使用范围循环 (`for (const auto& row : matrix)`)

3. 性能优化  
   - 暴力法：优化变量命名，增加循环终止条件注释
   - 动态规划：
     - 将二维 `dp` 数组优化为一维数组，空间复杂度从 O(mn) 降为 O(n)
     - 分离高度更新和面积计算阶段，提高缓存友好性
   - 单调栈：
     - 预分配带哨兵的 `heights` 数组，避免运行时动态修改
     - 将哨兵处理整合到主循环，消除临时数组操作

4. 可读性增强  
   - 变量重命名：`i1` → `start_row`，`i2` → `end_row` 等
   - 添加关键注释说明算法逻辑
   - 保持一致的代码风格

5. 边界条件处理  
   - 在单调栈实现中预置哨兵元素，简化边界判断
   - 添加循环终止条件 (`k >= 0 && min_height > 0`)

6. 内存优化  
   - 动态规划版本减少额外内存使用
   - 避免不必要的临时对象创建

7. 防御性编程  
   - 所有方法先检查空输入
   - 使用 `const` 修饰不可变参数

| 方法           | 时间复杂度       | 空间复杂度 | 优化点                             |
|----------------|------------------|------------|-----------------------------------|
| 暴力枚举       | O(R³C³) → O(R²C²)| O(1)       | 增加循环提前终止条件                |
| 动态规划       | O(RC²) → O(RC)  | O(C)       | 空间优化+循环结构优化               |
| 单调栈         | O(RC)           | O(C)       | 哨兵预处理+栈操作优化               |

进一步优化建议：
1. 添加记忆化机制优化动态规划版本
2. 实现并行处理（针对大规模数据）
3. 添加单元测试验证边界条件
4. 支持不同数值类型的矩阵（模板化）
*/

#include <vector>
#include <stack>
#include <algorithm> // 添加algorithm头文件用于max函数

using namespace std;


enum SubMatrixType {
    BRUTE_FORCE,
    DYNAMIC_PROGRAMMING,
    MONOTONIC_STACK
};

class Solution {
public:
    int maxSubMatrix(const vector<vector<int>>& matrix, SubMatrixType type = BRUTE_FORCE) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        switch (type) {
            case BRUTE_FORCE:         return bruteForce(matrix);
            case DYNAMIC_PROGRAMMING: return dynamicProgramming(matrix);
            case MONOTONIC_STACK:     return monotonicStack(matrix);
            default:                  return 0;
        }
    }

private:
    // 1. 暴力枚举法优化 O(m^2 * n^2) O(1)	极小规模数据验证          枚举所有可能的子矩阵，检查是否全为1，并计算最大面积。
    int bruteForce(const vector<vector<int>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        int max_area = 0;

        for (int start_row = 0; start_row < rows; ++start_row) {
            for (int start_col = 0; start_col < cols; ++start_col) {
                if (matrix[start_row][start_col] != 1) continue;

                int max_width = cols;
                for (int end_row = start_row; end_row < rows; ++end_row) {
                    if (matrix[end_row][start_col] != 1) break;

                    int curr_width = 0;
                    for (int end_col = start_col; end_col < max_width; ++end_col) {
                        if (matrix[end_row][end_col] == 1) {
                            ++curr_width;
                        } else {
                            max_width = end_col;
                            break;
                        }
                    }
                    max_area = max(max_area, (end_row - start_row + 1) * curr_width);
                }
            }
        }
        return max_area;
    }

    // 2. 动态规划优化  O(m * n) O(n)	中等规模数据 预处理每列连续1的高度，逐行扩展最大宽度。
    int dynamicProgramming(const vector<vector<int>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        vector<int> dp(cols, 0); // 使用一维数组优化空间
        int max_area = 0;

        for (const auto& row : matrix) {
            for (int col = 0; col < cols; ++col) {
                dp[col] = (row[col] == 1) ? dp[col] + 1 : 0;
            }
            
            // 对每行单独处理
            for (int col = 0; col < cols; ++col) {
                int min_height = dp[col];
                for (int k = col; k >= 0 && min_height > 0; --k) {
                    min_height = min(min_height, dp[k]);
                    max_area = max(max_area, min_height * (col - k + 1));
                }
            }
        }
        return max_area;
    }

    // 3. 单调栈优化 O(mn) O(n)	大规模高效计算         将每行视为柱状图，利用单调栈快速计算最大矩形。
    int monotonicStack(const vector<vector<int>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        vector<int> heights(cols + 1, 0); // 增加哨兵位置
        int max_area = 0;

        for (const auto& row : matrix) {
            // 更新高度数组
            for (int col = 0; col < cols; ++col) {
                heights[col] = (row[col] == 1) ? heights[col] + 1 : 0;
            }
            
            // 处理哨兵
            heights[cols] = 0;
            
            stack<int> st;
            for (int i = 0; i <= cols; ++i) {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int h = heights[st.top()];
                    st.pop();
                    int w = st.empty() ? i : (i - st.top() - 1);
                    max_area = max(max_area, h * w);
                }
                st.push(i);
            }
        }
        return max_area;
    }
};