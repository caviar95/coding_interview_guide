cmake_minimum_required(VERSION 3.10)
project(GetMinStackTest)

set(CMAKE_CXX_STANDARD 17)

# 添加 Google Test 子模块（假设 Google Test 源码在 googletest 目录下）
link_directories(../googletest)
include_directories(../googletest)

enable_testing()

# 添加测试可执行文件
add_executable(test_get_min test_get_min.cpp)

# 链接 Google Test 库
target_link_libraries(test_get_min gtest gtest_main)

# 添加测试
add_test(NAME GetMinStackTest COMMAND test_get_min)