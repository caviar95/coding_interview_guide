#include <gtest/gtest.h>
#include "max_sub_matrix.hpp"

/*
### 测试用例说明

1. 空矩阵测试  
   - 验证所有方法对空输入的处理
   - 预期结果：0
2. 全1矩阵测试  
   - 验证算法对完美矩形的识别
   - 预期结果：N×N（N为矩阵维度）
3. 单个元素测试  
   - 验证边界情况处理
   - 预期结果：1（当元素为1）或0（当元素为0）
4. 示例矩阵测试  
   - 验证算法对复杂情况的处理能力
   - 注意暴力法可能无法找到最优解（演示算法差异）
5. 特殊形状测试  
   - 单行/单列矩阵验证一维情况处理
   - 棋盘格矩阵验证离散分布处理
6. 性能测试  
   - 验证算法在大规模数据下的表现
   - 注意：暴力法不参与大规模测试

### 关键测试点

1. 算法正确性验证  
   - 通过不同形状的测试矩阵验证核心逻辑
   - 对比不同算法的结果一致性
2. 边界条件覆盖  
   - 空输入
   - 最小尺寸矩阵（1×1）
   - 全0/全1特殊情况
3. 性能差异验证  
   - 暴力法只用于小规模验证
   - 动态规划和单调栈算法验证大规模处理能力
4. 错误处理验证  
   - 包含0值中断情况的处理
   - 非连续最大矩形的识别
*/

class MaxSubMatrixTest : public ::testing::Test {
protected:
    Solution solution;
    
    // 测试用例矩阵
    std::vector<std::vector<int>> emptyMatrix = {};
    std::vector<std::vector<int>> singleElement1 = {{1}};
    std::vector<std::vector<int>> singleElement0 = {{0}};
    std::vector<std::vector<int>> allOnes = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    std::vector<std::vector<int>> sample1 = {
        {1,0,1,1,1},
        {0,1,1,1,1},
        {0,1,1,1,1},
        {0,1,1,0,1}
    };
    std::vector<std::vector<int>> singleRow = {{1,0,1,1,0,1}};
    std::vector<std::vector<int>> singleColumn = {{1},{1},{0},{1},{1}};
    std::vector<std::vector<int>> chessBoard = {
        {1,0,1},
        {0,1,0},
        {1,0,1}
    };
};

// 测试空矩阵
TEST_F(MaxSubMatrixTest, TestEmptyMatrix) {
    EXPECT_EQ(solution.maxSubMatrix(emptyMatrix, BRUTE_FORCE), 0);
    EXPECT_EQ(solution.maxSubMatrix(emptyMatrix, DYNAMIC_PROGRAMMING), 0);
    EXPECT_EQ(solution.maxSubMatrix(emptyMatrix, MONOTONIC_STACK), 0);
}

// 测试全1矩阵
TEST_F(MaxSubMatrixTest, TestAllOnes) {
    const int expected = 9;
    EXPECT_EQ(solution.maxSubMatrix(allOnes, BRUTE_FORCE), expected);
    EXPECT_EQ(solution.maxSubMatrix(allOnes, DYNAMIC_PROGRAMMING), expected);
    EXPECT_EQ(solution.maxSubMatrix(allOnes, MONOTONIC_STACK), expected);
}

// 测试单个元素
TEST_F(MaxSubMatrixTest, TestSingleElement) {
    EXPECT_EQ(solution.maxSubMatrix(singleElement1, BRUTE_FORCE), 1);
    EXPECT_EQ(solution.maxSubMatrix(singleElement0, BRUTE_FORCE), 0);
}

// 测试示例矩阵
TEST_F(MaxSubMatrixTest, TestSample1) {
    const int expected = 9;
    EXPECT_EQ(solution.maxSubMatrix(sample1, BRUTE_FORCE), expected);
    EXPECT_EQ(solution.maxSubMatrix(sample1, DYNAMIC_PROGRAMMING), expected);
    EXPECT_EQ(solution.maxSubMatrix(sample1, MONOTONIC_STACK), expected);
}

// 测试单行矩阵
TEST_F(MaxSubMatrixTest, TestSingleRow) {
    const int expected = 2;
    EXPECT_EQ(solution.maxSubMatrix(singleRow, BRUTE_FORCE), expected);
    EXPECT_EQ(solution.maxSubMatrix(singleRow, DYNAMIC_PROGRAMMING), expected);
    EXPECT_EQ(solution.maxSubMatrix(singleRow, MONOTONIC_STACK), expected);
}

// 测试单列矩阵
TEST_F(MaxSubMatrixTest, TestSingleColumn) {
    const int expected = 2;
    EXPECT_EQ(solution.maxSubMatrix(singleColumn, BRUTE_FORCE), expected);
    EXPECT_EQ(solution.maxSubMatrix(singleColumn, DYNAMIC_PROGRAMMING), expected);
    EXPECT_EQ(solution.maxSubMatrix(singleColumn, MONOTONIC_STACK), expected);
}

// 测试棋盘格矩阵
TEST_F(MaxSubMatrixTest, TestChessBoard) {
    const int expected = 1;
    EXPECT_EQ(solution.maxSubMatrix(chessBoard, BRUTE_FORCE), expected);
    EXPECT_EQ(solution.maxSubMatrix(chessBoard, DYNAMIC_PROGRAMMING), expected);
    EXPECT_EQ(solution.maxSubMatrix(chessBoard, MONOTONIC_STACK), expected);
}

// 测试性能边界（需要根据实际情况调整矩阵大小）
TEST_F(MaxSubMatrixTest, TestLargeMatrix) {
    const int N = 50;  // 控制测试规模
    std::vector<std::vector<int>> largeMatrix(N, std::vector<int>(N, 1));
    
    EXPECT_EQ(solution.maxSubMatrix(largeMatrix, DYNAMIC_PROGRAMMING), N*N);
    EXPECT_EQ(solution.maxSubMatrix(largeMatrix, MONOTONIC_STACK), N*N);
}
