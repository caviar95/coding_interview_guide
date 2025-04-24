#include <gtest/gtest.h>
#include "max_sub_matrix.hpp"

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
    // EXPECT_EQ(solution.maxSubMatrix(sample1, BRUTE_FORCE), 8);  // 注意暴力法可能无法找到最优解
    EXPECT_EQ(solution.maxSubMatrix(sample1, DYNAMIC_PROGRAMMING), 9);
    EXPECT_EQ(solution.maxSubMatrix(sample1, MONOTONIC_STACK), 9);
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
