#include <gtest/gtest.h>
#include "arrays/0001_two_sum.hpp"

// Test Case 1: Standard input
TEST(TwoSumTest, HandlesStandardCase) {
    Solution sol;
    vector<int> nums = {2, 7, 11, 15};
    vector<int> expected = {0, 1};
    EXPECT_EQ(sol.twoSum(nums, 9), expected);
}

// Test Case 2: Unordered input
TEST(TwoSumTest, HandlesUnorderedInput) {
    Solution sol;
    vector<int> nums = {3, 2, 4};
    vector<int> expected = {1, 2};
    EXPECT_EQ(sol.twoSum(nums, 6), expected);
}

// Test Case 3: Duplicates
TEST(TwoSumTest, HandlesDuplicates) {
    Solution sol;
    vector<int> nums = {3, 3};
    vector<int> expected = {0, 1};
    EXPECT_EQ(sol.twoSum(nums, 6), expected);
}