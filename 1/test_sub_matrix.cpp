#include <gtest/gtest.h>
#include "max_sub_matrix.hpp"

class SolutionTest : public ::testing::Test {
protected:
    Solution solution;
};

TEST_F(SolutionTest, MaxSubMatrixEnum_EmptyMatrix) {
    std::vector<std::vector<int>> matrix = {};
    EXPECT_EQ(solution.maxSubMatrix(matrix, ENUM), 0);
}

TEST_F(SolutionTest, MaxSubMatrixEnum_SingleElement) {
    std::vector<std::vector<int>> matrix = {{1}};
    EXPECT_EQ(solution.maxSubMatrix(matrix, ENUM), 1);
}

TEST_F(SolutionTest, MaxSubMatrixEnum_AllZeros) {
    std::vector<std::vector<int>> matrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    EXPECT_EQ(solution.maxSubMatrix(matrix, ENUM), 0);
}

TEST_F(SolutionTest, MaxSubMatrixEnum_SimpleCase) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    EXPECT_EQ(solution.maxSubMatrix(matrix, ENUM), 4);  // The 2x2 submatrix of 1s
}

// 类似地，为DP和单调栈方法编写测试用例
TEST_F(SolutionTest, MaxSubMatrixDP_SimpleCase) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    EXPECT_EQ(solution.maxSubMatrix(matrix, DP), 4);
}

TEST_F(SolutionTest, MaxSubMatrixMonotonic_SimpleCase) {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    EXPECT_EQ(solution.maxSubMatrix(matrix, STACK), 4);
}

// 更多边界条件和复杂案例的测试...